/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 12:19:45 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void 			read_cmd(t_client *client, int r)
{
	while ((r = read(client->sock, client->buff, 1)) > 0 && client->buff[0] != '\0')
	{
		client->buff[r] = '\0';
		write(1, client->buff, r);
	}
}

int						gest_client(t_client *client, char *login)
{
	int					r;

	client->buff[client->read - 1] = '\0';
	write(client->sock, client->buff, client->read);
	if (ft_strncmp("get ", client->buff, 4) == 0)
		get_get_client(client);
	else if (ft_strncmp("put ", client->buff, 4) == 0)
		get_put_client(client);
	else if (ft_strcmp("lpwd", client->buff) == 0)
		lpwd(client->sock);
	else if (!ft_strncmp(client->buff, "lcd", 2))
		lcd(client->buff, client->sock);
	else if (ft_strcmp("quit", client->buff) == 0)
	{
		ft_printcolor("SUCCESS", 32);
		ft_putchar('\n');
		exit(0);
	}
	else
		read_cmd(client, r);
	ft_printf("[", login);
	ft_printcolor(login, 31);
	ft_printf("] / >", login);
	return (0);
}
