/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/29 16:14:01 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void				read_client_cmd(t_client *client)
{
	int					i;
	int					read2;

	i = 0;
	while ((read2 = read(client->sock, client->buff, 1)) > 0 &&
	client->buff[0] != '\0')
	{
		client->buff[read2] = '\0';
		write(1, client->buff, read2);
	}
}

static int				gest_client2(t_client *client)
{
	if (ft_strnequ(client->buff, "lcd ", 4))
		lcd(client->buff);
	else if (ft_strequ(client->buff, "lls"))
		lls();
	else if (ft_strequ(client->buff, "lpwd"))
		lpwd();
	else if (ft_strnequ(client->buff, "lmkdir ", 7))
		lmkdir(client->buff);
	else if (ft_strnequ(client->buff, "lrmdir ", 7))
		lrmdir(client->buff);
	else if (ft_strnequ(client->buff, "lrm ", 4))
		lrm(client->buff);
	else
		return (0);
	return (1);
}

int						gest_client(t_client *client, char *login)
{
	ft_putendl_fd(client->buff, client->sock);
	if (ft_strnequ(client->buff, "get ", 4))
		get_get_client(client);
	else if (ft_strnequ(client->buff, "put ", 4))
		get_put_client(client);
	else if (gest_client2(client) == 1)
		;
	else if (ft_strequ(client->buff, "quit"))
	{
		ft_printcolor("SUCCESS\n", 32);
		exit(0);
	}
	else
		read_client_cmd(client);
	ft_printf("[", login);
	ft_printcolor(login, 33);
	ft_printf("] / >", login);
	return (0);
}
