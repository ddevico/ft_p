/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_serveur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 19:26:27 by davydevico       ###   ########.fr       */
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
	if (!ft_strncmp("put ", serv->buff, 4) || !ft_strcmp("put",
	serv->buff))
		get_put(serv);
	else if (!ft_strncmp(serv->buff, "get ", 3))
		get_get(serv);
	else if (!ft_strcmp(serv->buff, "ls"))
		get_ls(serv->client);
	else if (!ft_strncmp(serv->buff, "cd", 2) || !ft_strcmp(serv->buff, "cd"))
		get_cd(serv->buff, serv);
	else if (!ft_strcmp(serv->buff, "pwd"))
		get_pwd(serv->client);
	else if (!ft_strcmp(serv->buff, "quit") || !ft_strcmp(serv->buff, "lpwd")
		|| !ft_strncmp(serv->buff, "lcd", 2) || !ft_strcmp(serv->buff, "lcd")
		|| !ft_strcmp(serv->buff, "lls"))
		;
	else
		get_error(serv->client);
	return (1);
}

int			gest_serveur(t_serv *serv)
{
	while (1)
	{
		if ((serv->read = read(serv->client, serv->buff, 1024)) > 0)
		{
			serv->buff[serv->read - 1] = '\0';
			if (gest_command(serv))
				if (!ft_strcmp(serv->buff, "quit"))
					break ;
		}
		ft_bzero(serv->buff, 1024);
	}
	ft_printf("Disconnected from client\n");
	close(serv->client);
	return (0);
}
