/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_serveur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/29 10:35:38 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void	get_error(int client)
{
	ft_putendl_fd("\033[31mERROR: Command not found\033[0m", client);
	write(client, "\0", 1);
}

static int	gest_command(t_serv *serv)
{
	if (ft_strnequ(serv->buff, "put ", 4))
		get_put(serv);
	else if (ft_strnequ(serv->buff, "get ", 4))
		get_get(serv);
	else if (ft_strequ(serv->buff, "ls"))
		get_ls(serv->client);
	else if (ft_strnequ(serv->buff, "cd ", 3))
		get_cd(serv->buff, serv);
	else if (ft_strequ(serv->buff, "pwd"))
		get_pwd(serv->client);
	else if (ft_strnequ(serv->buff, "mkdir ", 6))
		get_mkdir(serv->buff, serv);
	else if (ft_strnequ(serv->buff, "rmdir ", 6))
		get_rmdir(serv->buff, serv);
	else if (ft_strnequ(serv->buff, "rm ", 3))
		get_rm(serv->buff, serv);
	else if (ft_strequ(serv->buff, "quit") || ft_strequ(serv->buff, "lpwd")
		|| ft_strnequ(serv->buff, "lcd ", 4) || ft_strequ(serv->buff, "lls")
		|| ft_strnequ(serv->buff, "lmkdir ", 7)
		|| ft_strnequ(serv->buff, "lrmdir ", 7)
		|| ft_strnequ(serv->buff, "lrm ", 4))
		;
	else
		get_error(serv->client);
	return (1);
}

int			gest_serveur(t_serv *serv)
{
	while (1)
	{
		serv->read = ft_get_next_line(serv->client, &serv->buff);
		if (serv->read > 0)
		{
			if (gest_command(serv))
				if (!ft_strcmp(serv->buff, "quit"))
					break ;
			free(serv->buff);
		}
		else
			break ;
	}
	ft_printf("Disconnected from client\n");
	close(serv->client);
	return (0);
}
