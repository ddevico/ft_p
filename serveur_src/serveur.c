/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 17:08:59 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static int				init_serveur(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	addr;

	if (port == 0)
		return (print_error("ERROR: invalid port\n"));
	if ((proto = getprotobyname("TCP")) == NULL)
		return (print_error("ERROR: getprotobyname() failed\n"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (print_error("ERROR: socket() failed\n"));
	ft_memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&addr, sizeof(addr))) == -1)
		return (print_error("ERROR: bind() failed\n"));
	if (listen(sock, 3) == -1)
		return (print_error("ERROR: listen() failed\n"));
	return (sock);
}

static void				test_pass(t_serv *serv)
{
	if ((server_login(serv->client)) == -1)
	{
		close(serv->client);
		close(serv->sock);
	}
}

static int				active_server(t_serv *serv, unsigned int id, int cli)
{
	pid_t				pid;
	struct sockaddr_in	csin;
	unsigned int		cslen;

	while (42)
	{
		if ((cli = accept(serv->sock, (struct sockaddr *)&csin, &cslen)) == -1)
			ft_printf("Connection from client[%u] refused\n", ++id);
		else
		{
			ft_printf("Connection from client [%u] accepted\n", ++id);
			if ((pid = fork()) == -1)
			{
				close(cli);
				return (ft_printf("ERROR : fork() failed\n"));
			}
			else if (pid == 0)
			{
				test_pass(serv);
				gest_serveur(serv);
			}
		}
		close(cli);
	}
	return (0);
}

static int				init_struct(t_serv *serv, char *av)
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
	{
		ft_printf("error: usage: %s <port>\n", av[0]);
		return (-1);
	}
	if (init_struct(&serv, av[1]) == -1)
		return (-1);
	ft_putendl("Waiting for connections...");
	loop = active_server(serv->client, &serv, 0);
	close(serv.sock);
	return (ac);
}
