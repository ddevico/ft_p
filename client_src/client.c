/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/28 16:24:56 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void					signalstop(int c)
{
	(void)c;
	signal(SIGTSTP, signalstop);
	ft_printf("SIGTSTP Catch\n");
}

static int				init_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (port == 0)
		return (print_error("error: invalid port\n"));
	if ((proto = getprotobyname("TCP")) == NULL)
		return (print_error("error: getprotobyname() failed\n"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (print_error("error: socket() failed\n"));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (ft_strequ(addr, "localhost") == 1)
		addr = "127.0.0.1";
	sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		return (print_error("error: Connect() failed\n"));
	return (sock);
}

static int				login_password(t_client *client, char **login)
{
	char				buff[1024];
	char				*line;
	char				*line2;

	ft_putendl("Login:");
	get_next_line(0, &line);
	*login = ft_strdup(line);
	ft_putendl("Password:");
	get_next_line(0, &line2);
	line = ft_strjoin(line, ":");
	line = ft_strjoin(line, line2);
	send(client->sock, line, ft_strlen(line) + 1, 0);
	recv(client->sock, buff, 1023, 0);
	if (!(ft_strcmp(buff, "WRONG_PASS")))
	{
		ft_printcolor("ERROR: Wrong Password\n", 31);
		close(client->sock);
		return (-1);
	}
	ft_printf("Welcome %s !\n", *login);
	return (0);
}

int						main(int ac, char **av)
{
	t_client			client;
	int					ret;
	char				*login;

	signal(SIGTSTP, signalstop);
	if (ac != 3)
	{
		ft_printf("error: usage: %s <port>\n", av[0]);
		close(client.sock);
		return (-1);
	}
	if ((client.sock = init_client(av[1], ft_atoi(av[2]))) == -1)
	{
		close(client.sock);
		return (0);
	}
	if (login_password(&client, &login) == -1)
		return (0);
	ft_printf("[", login);
	ft_printcolor(login, 33);
	ft_printf("] / >", login);
	while ((ret = ft_get_next_line(0, &client.buff)) > 0)
		gest_client(&client, login);
	close(client.sock);
	return (ac);
}
