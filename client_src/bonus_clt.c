/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/29 10:16:07 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int					lrmdir(char *buff)
{
	char			**path;

	path = ft_strsplit(buff, ' ');
	if (!path[1])
		ft_printcolor("ERROR: No path specified\n", 31);
	else if (rmdir(path[1]) == 0)
		ft_printcolor("SUCCESS\n", 32);
	else
		ft_printcolor("ERROR: lrmdir\n", 31);
	return (1);
}

int					lmkdir(char *buff)
{
	char			**path;

	path = ft_strsplit(buff, ' ');
	if (!path[1])
		ft_printcolor("ERROR: No path specified\n", 31);
	else if (mkdir(path[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0)
		ft_printcolor("SUCCESS\n", 32);
	else
		ft_printcolor("ERROR: lmkdir\n", 31);
	return (1);
}

int					lcd(char *buff)
{
	char			**path;

	path = ft_strsplit(buff, ' ');
	if (path[1] && chdir(path[1]) == -1)
	{
		ft_printcolor("ERROR: lcd\n", 31);
		return (0);
	}
	ft_printcolor("SUCCESS\n", 32);
	return (1);
}

int					lpwd(void)
{
	char			*pwd;

	pwd = ft_strnew(1024);
	if (!getcwd(pwd, 1023))
	{
		ft_printcolor("ERROR: lpwd\n", 31);
		return (0);
	}
	ft_putendl(pwd);
	ft_printcolor("SUCCESS\n", 32);
	return (1);
}

int					lls(void)
{
	DIR				*dir;
	struct dirent	*p;
	char			*fic;

	if (!(dir = opendir(".")))
		ft_printcolor("ERROR: lls\n", 31);
	while ((p = readdir(dir)))
	{
		fic = p->d_name;
		if (ft_strncmp(".", fic, 1) != 0)
			ft_putendl(fic);
	}
	ft_printcolor("SUCCESS\n", 32);
	closedir(dir);
	return (1);
}
