/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/15 18:20:44 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static void				add_space(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
			s[i] = ' ';
	}
}

static int				get_cd(char **command, int client)
{
	char				buff[BUFF_SIZE + 1];
	char				*tmp;

	ft_bzero(buff, BUFF_SIZE);
	if (!(command[1]) || (command[1] && command[2]))
	{
		ft_strcpy(buff, "Error ==> cd <path>\n\0");
		send(client, (const void *)buff, 25, 0);
	}
	else
	{
		if (chdir(command[1]) < 0)
			ft_strcpy(buff, "Error parameter\n\0");
		else
			ft_strcpy(buff, "CD SUCCESS\n\0");
		send(client, (const void *)buff, ft_strlen(buff), 0);
	}
	return (0);
}

static void    ls_main_simple()
{
    DIR                *dir;
    struct dirent    *file;
    struct stat        sb;
	pid_t					pid;

	pid = fork();
    dir = opendir(".");
    file = NULL;
    while ((file = readdir(dir)) != NULL)
    {
        if (file->d_name[0] != '.')
            printf("%s\n", file->d_name);
    }
}

int					option_ls(int sock)
{
	int				r;
	char			buf[1024];
	int				i;

	ft_bzero(buf, 1023);
	i = 0;
	while ((r = read(sock, buf, 1023)) > 0)
	{
		i++;
		buf[r] = '\0';
		ft_putstr(buf);
		if (ft_strchr(buf, '\x2') != NULL)
			break ;
		ft_bzero(buf, 1023);
	}
	return (1);
}


static int						gest_command(char **command, int client)
{
	int					test;

	test = 0;
	if (ft_strcmp(command[0], "put") == 0)
	{
		test = 1;
	}
	else if (ft_strcmp(command[0], "get") == 0)
	{
		test = 1;
	}
	else if (ft_strcmp(command[0], "ls") == 0)
	{
		option_ls(client);
		test = 1;
	}
 	else if (ft_strcmp(command[0], "cd") == 0)
	{
		get_cd(command, client);
		test = 1;
	}
	else if (ft_strcmp(command[0], "pwd") == 0)
	{
		test = 1;
	}
	return (test);
}

int						gest_client(int socket, int client)
{
	char				*message;
	char				buff[1024];

	message = ft_strdup("Connected !\n");
	send(client, (const void *)message, 14, 0);
	while (1)
	{
		if ((socket = recv(client, buff, 1024, 0) > 0))
		{
			add_space(buff);
			if (gest_command(ft_strsplit(buff, ' '), client))
				ft_printf("\n");
			else
			{
				if (!ft_strcmp(*ft_strsplit(buff, ' '), "quit"))
					break ;
			}
		}
	}
	ft_printf("Disconnected from client\n");
	close(client);
	return (0);
}
