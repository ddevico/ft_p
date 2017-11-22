/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/22 13:51:21 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void				read_cmd(t_client *client)
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
	if (!ft_strncmp(client->buff, "lcd", 2))
		lcd(client->buff);
	else if (!ft_strcmp(client->buff, "lls"))
		lls();
	else if (!ft_strcmp("lpwd", client->buff))
		lpwd();
	else if (!ft_strncmp(client->buff, "lmkdir ", 6))
		lmkdir(client->buff);
	else if (!ft_strncmp(client->buff, "lrmdir ", 6))
		lrmdir(client->buff);
	else
		return (0);
	return (1);
}

int						gest_client(t_client *client, char *login)
{
	client->buff[client->read - 1] = '\0';
	write(client->sock, client->buff, client->read);
	if (!ft_strncmp("get ", client->buff, 4) || !ft_strcmp("get", client->buff))
		get_get_client(client);
	else if (ft_strnequ(client->buff, "put ", 4))
		get_put_client(client);
	else if (gest_client2(client) == 1)
		;
	else if (ft_strcmp("quit", client->buff) == 0)
	{
		ft_printcolor("SUCCESS\n", 32);
		exit(0);
	}
	else
		read_cmd(client);
	ft_printf("[", login);
	ft_printcolor(login, 33);
	ft_printf("] / >", login);
	return (0);
}
