/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/20 11:26:24 by davydevico       ###   ########.fr       */
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		return (print_error("error: Connect() failed\n"));
	return (sock);
}

int						main(int ac, char **av)
{
	int					sock;
	int					loop;
	t_client			client;

	if (ac != 3)
		return (usage(av[0]));
	client.sock = init_client(av[1], ft_atoi(av[2]));
	ft_printf("ft_p> ");
	while ((client.read = read(0, client.buff, 1023)) > 0)
		gest_client(&client);
	close(client.sock);
	return (ac);
}
