/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 21:53:20 by davydevico       ###   ########.fr       */
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
		ft_putendl_fd("FILE_ERROR", sock);
	}
	else
		ft_putendl_fd("FILE_OK", sock);
	return (file);
}

static void		run_get_client(int sock, int file, int totsize)
{
	char		*buf;
	int			size;
	int			n;

	n = 0;
	buf = malloc(sizeof(char) * totsize);
	while (n < totsize)
	{
		size = recv(sock, buf + n, 4096, 0);
		n += size;
	}
	write(file, buf, totsize);
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
	ft_putendl_fd("GO_SEND", sock);
	return (size);
}

void			get_get_client(t_client *client)
{
	int			file;
	int			size;
	char		*line;

	if (alert_message_client("FILE_SRV_OK", client->sock) < 1)
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
	if (ft_get_next_line(client->sock, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	close(file);
}
