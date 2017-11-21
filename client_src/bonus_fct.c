/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 12:22:14 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int			lcd(char *buff, int sock)
{
	char			**path;

	path = ft_strsplit(buff, ' ');
	if (path[1] && chdir(path[1]) == -1)
	{
		ft_printcolor("ERROR", 31);
		return (0);
	}
	ft_printcolor("ERROR", 32);
	return (1);
}

int			lpwd(int sock)
{
	char	*pwd;

	pwd = ft_strnew(1024);
	if (!getcwd(pwd, 1023))
	{
		ft_putendl("ERROR");
		return (0);
	}
	ft_putendl(pwd);
	return (1);
}

int			lls(char **av, int fd)
{
	pid_t	father;
	int		status;
	char	*av_ls[3];

	(void)fd;
	av_ls[0] = ft_strdup("ls");
	av_ls[1] = av[1];
	av_ls[2] = NULL;
	father = fork();
	if (father > 0)
		wait4(father, &status, 0, 0);
	if (father == 0)
	{
		if (execv("/bin/ls", av_ls) == -1)
			exit(-1);
	}
	free(av_ls[0]);
	return (1);
}
