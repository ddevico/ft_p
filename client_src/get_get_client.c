/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/23 14:28:48 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static int		open_file(char *cmd, int sock)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
	{
		ft_printcolor("ERROR : can't create the file, already exists\n", 31);
		ft_putendl_fd("ERROR_FD", sock);
	}
	else
		ft_putendl_fd("VERIF_FD", sock);
	return (file);
}

static void		run_get_client(int sock, int file, int totsize)
{
	char		*buff;
	int			size;
	int			n;

	n = 0;
	buff = malloc(sizeof(char) * totsize);
	if (!buff)
		exit(1);
	while (n < totsize)
	{
		size = recv(sock, buff + n, 4096, 0);
		n += size;
	}
	write(file, buff, totsize);
}

static int		size_file(int sock)
{
	int			size;
	char		*line;

	size = 0;
	if (ft_get_next_line(sock, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
		{
			ft_putendl(line);
			ft_putendl_fd("ERROR_FILESIZE", sock);
			free(line);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	ft_putendl_fd("SEND", sock);
	return (size);
}

static void		get_get_next(t_client *client)
{
	char		*line;

	if (ft_get_next_line(client->sock, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
}

void			get_get_client(t_client *client)
{
	int			file;
	int			size;

	if (alert_message_client("SERVER_OK", client->sock) < 1)
	{
		ft_printcolor("ERROR : open() file\n", 31);
		return ;
	}
	if ((file = open_file(client->buff, client->sock)) == -1)
		return ;
	if (alert_message_client("TEST_OK", client->sock) < 1)
	{
		ft_printcolor("\033[31mERROR : mmap()\033[0m\n", 32);
		return ;
	}
	if ((size = size_file(client->sock)) == -1)
		return ;
	run_get_client(client->sock, file, size);
	ft_putendl_fd("SUCCESS", client->sock);
	get_get_next(client);
	close(file);
}
