/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/22 00:06:50 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void 				get_mkdir(char *command, t_serv *serv)
{
	char			**path;

	path = ft_strsplit(command, ' ');
	if (!path[1])
		return ;
	if (mkdir(path[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
		ft_putendl_fd("\033[31mSUCCESS\033[0m", serv->client);
	else
		ft_putendl_fd("\033[31mERROR: mkdir\033[0m", serv->client);
}

void				get_cd(char *command, t_serv *serv)
{
	char			newpwd[1024];
	int				drap;
	char			**path;

	drap = 1;
	path = ft_strsplit(command, ' ');
	if (chdir(path[1]) == -1)
	{
		ft_putendl_fd("\033[31mERROR: Repository doesn't exist\033[0m",
		serv->client);
		drap = 0;
	}
	getcwd(newpwd, 1024);
	if (ft_strcmp(serv->pwd, newpwd) > 0 || ft_strnequ(path[1], "/", 1))
	{
		chdir(serv->pwd);
		ft_putendl_fd("\033[31mERROR: No permission to access here\033[0m",
		serv->client);
		drap = 0;
	}
	if (drap == 1)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
	write(serv->client, "\0", 1);
}

void				get_ls(int client)
{
	DIR				*dir;
	struct dirent	*p;
	char			*fic;

	if (!(dir = opendir(".")))
		ft_putendl_fd("\033[31mERROR: ls failed\033[0m", client);
	while ((p = readdir(dir)))
	{
		fic = p->d_name;
		if (ft_strncmp(".", fic, 1) != 0)
			ft_putendl_fd(fic, client);
	}
	ft_putendl_fd("\033[32mSUCCESS\033[0m", client);
	write(client, "\0", 1);
	closedir(dir);
}

void				get_pwd(int client)
{
	char			pwd[1024];

	getcwd(pwd, 1024);
	ft_putendl_fd(pwd, client);
	ft_putendl_fd("\033[32mSUCCESS\033[0m", client);
	write(client, "\0", 1);
}
