/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 15:50:51 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static int						gest_command(t_serv *serv)
{
	if (!ft_strncmp(serv->buff, "put ", 3))
		get_put(serv);
	else if (!ft_strncmp(serv->buff, "get ", 3))
		get_get(serv);
	else if (!ft_strcmp(serv->buff, "ls"))
		get_ls(serv->client);
 	else if (!ft_strncmp(serv->buff, "cd ", 3) || !ft_strcmp(serv->buff, "cd"))
		get_cd(serv->buff, serv);
	else if (!ft_strcmp(serv->buff, "pwd"))
		get_pwd(serv->client);
	return (1);
}

int						gest_serveur(t_serv *serv)
{
	while (1)
	{
		if ((serv->read = read(serv->client, serv->buff, 1024)) > 0)
		{
			serv->buff[serv->read - 1] = '\0';
			if (gest_command(serv))
				;
			else
			{
				if (!ft_strcmp(serv->buff, "quit"))
					break ;
				//ft_putendl_fd("ERROR: Command not found", serv->client);
			}
		}
		ft_bzero(serv->buff, 1024);
	}
	ft_printf("Disconnected from client\n");
	close(serv->client);
	return (0);
}
