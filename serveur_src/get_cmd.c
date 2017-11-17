/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 11:41:53 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void				get_cd(char **command, t_serv *serv)
{
	char			newpwd[1024];
	int				k;

	k = 1;
	if (chdir(command[1]) == -1)
	{
		ft_putendl_fd("ERROR: Repository doesn't exist", serv->client);
		return ;
	}
	getcwd(newpwd, 1024);
	printf("%s\n", newpwd);
	if (ft_strcmp(serv->pwd, newpwd) > 0 || ft_strnequ(command[1], "/", 1))
	{
		chdir(serv->pwd);
		ft_putstr_fd("ERROR: No permission to access here\n", serv->client);
		return ;
	}
	ft_putendl_fd("SUCCESS", serv->client);
	write(serv->client, "\0", 1);
}

void    			get_ls(int client)
{
	DIR				*dir;
	struct dirent	*p;
	char			*fic;

	if (!(dir = opendir(".")))
		ft_putendl_fd("ERROR: ls failed\n", client);
	while ((p = readdir(dir)))
	{
		fic = p->d_name;
		if (ft_strncmp(".", fic, 1) != 0)
			ft_putendl_fd(fic, client);
	}
	ft_putendl_fd("\nSUCCESS", client);
	write(client, "\0", 1);
	closedir(dir);
}

void				get_pwd(int client)
{
	char			pwd[1024];

	getcwd(pwd, 1024);
	ft_putendl_fd(pwd, client);
	ft_putendl_fd("SUCCESS\n", client);
	write(client, "\0", 1);
}
