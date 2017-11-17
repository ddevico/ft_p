/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 12:22:59 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void						gest_command(char **command, t_serv *serv)
{
	if (!command[0])
		return ;
	else if (ft_strcmp(command[0], "put") == 0)
		get_put(serv);
	else if (ft_strcmp(command[0], "get") == 0)
		get_get(serv);
	else if (ft_strcmp(command[0], "ls") == 0)
		get_ls(serv->client);
 	else if (ft_strcmp(command[0], "cd") == 0)
		get_cd(command, serv);
	else if (ft_strcmp(command[0], "pwd") == 0)
		get_pwd(serv->client);
}

static int						test_command(char **command, t_serv *serv)
{
	int					test;

	test = 0;
	if (!command[0])
		test = 1;
	else if (ft_strcmp(command[0], "put") == 0)
		test = 1;
	else if (ft_strcmp(command[0], "get") == 0)
		test = 1;
	else if (ft_strcmp(command[0], "ls") == 0)
		test = 1;
 	else if (ft_strcmp(command[0], "cd") == 0)
		test = 1;
	else if (ft_strcmp(command[0], "pwd") == 0)
		test = 1;
	return (test);
}

int						gest_client(t_serv *serv)
{
	char				**mess;

	ft_putendl_fd("Connected !", serv->client);
	while (1)
	{
		ft_putendl_fd_backslach("ft_p> ", serv->client);
		if ((serv->read = read(serv->client, serv->buff, 1024) > 0))
		{
			add_space(serv->buff);
			mess = ft_strsplit(serv->buff, ' ');
			if (test_command(mess, serv))
				gest_command(mess, serv);
			else
			{
				if (!ft_strcmp(*mess, "quit"))
					break ;
				ft_putendl_fd("ERROR: Command not found", serv->client);
			}
		}
		ft_bzero(serv->buff, 1024);
	}
	ft_printf("Disconnected from client\n");
	close(serv->client);
	return (0);
}
