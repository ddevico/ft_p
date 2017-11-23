/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_serv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/23 11:35:49 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void				get_rmdir(char *command, t_serv *serv)
{
	char			**path;

	path = ft_strsplit(command, ' ');
	if (!path[1])
		ft_putendl_fd("\033[31mERROR: No path specified\033[0m", serv->client);
	else if (rmdir(path[1]) == 0)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
	else
		ft_putendl_fd("\033[31mERROR: rmdir\033[0m", serv->client);
	write(serv->client, "\0", 1);
}

void				get_mkdir(char *command, t_serv *serv)
{
	char			**path;

	path = ft_strsplit(command, ' ');
	if (!path[1])
		ft_putendl_fd("\033[31mERROR: No path specified\033[0m", serv->client);
	else if (mkdir(path[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
	else
		ft_putendl_fd("\033[31mERROR: mkdir\033[0m", serv->client);
	write(serv->client, "\0", 1);
}


void				get_rm(char *command, t_serv *serv)
{
	char			**path;

	path = ft_strsplit(command, ' ');
	if (!path[1])
		ft_putendl_fd("\033[31mERROR: No path specified\033[0m", serv->client);
	else if (unlink(path[1]) == 0)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
	else
		ft_putendl_fd("\033[31mERROR: rm\033[0m", serv->client);
	write(serv->client, "\0", 1);
}
