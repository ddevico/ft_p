/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:19 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static int 			usage(char *str) {
	ft_printf("error: usage: %s <port>\n", str);
	return (-1);
}

static int 			print_error(char *str) {
	ft_printf("%s", str);
	return (-1);
}

static int				init_serveur(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	addr;

	if (port == 0)
		return (print_error("error: invalid port\n"));
	if ((proto = getprotobyname("TCP")) == NULL)
		return (print_error("error: getprotobyname() failed\n"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (print_error("error: socket() failed\n"));
	ft_memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&addr, sizeof(addr))) == -1)
		return (print_error("error: bind() failed\n"));
	if (listen(sock, 3) == -1)
		return (print_error("error: listen() failed\n"));
	return (sock);
}

static int				active_server(t_serv *serv, unsigned int id)
{
	pid_t				pid;

	while (42)
	{
		if ((serv->client = accept(serv->sock, (struct sockaddr *)NULL, NULL)) == -1)
			ft_printf("Connection from client[%u] refused\n", ++id);
		else
		{
			ft_printf("Connection from client [%u] accepted\n", ++id);
			if ((pid = fork()) == -1)
			{
				close(serv->client);
				close(serv->sock);
				return (ft_printf("fatal error: fork() failed\n"));
			}
			else if (pid == 0)
				gest_client(serv);
			close(serv->client);
		}
	}
	return (0);
}

static int	init_struct(t_serv *serv, char *av)
{
	serv->counter = 0;
	serv->port = ft_atoi(av);
	if ((serv->sock = init_serveur(serv->port)) == -1)
		return (-1);
	getcwd(serv->pwd, 1024);
	return (0);
}

int						main(int ac, char **av)
{
	int					sock;
	int					loop;
	t_serv				serv;

	if (ac != 2)
		return (usage(av[0]));
	if (init_struct(&serv, av[1]) == -1)
		return (-1);
	ft_putendl("Waiting for incoming connections...");
	loop = active_server(&serv, 0);
	close(serv.sock);
	return (ac);
}
