/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 15:00:31 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

static int			open_file(char *cmd, int sock)
{
	char			*filename;
	int				file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
		ft_putendl_fd("FILE_ERROR", sock);
	else
		ft_putendl_fd("FILE_OK", sock);
	return (file);
}

static void 		run_put(int sock, int file, int totsize)
{
	char			*buf;
	int				size;
	int				n;

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
	int				size;
	char			*line;

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

void				get_put(t_serv *serv)
{
	int				file;
	int				size;

	if (alert_message("FILE_CLT_OK", serv->client) < 1)
		return ;
	if ((file = open_file(serv->buff, serv->client)) == -1)
		return ;
	if ((size =size_file(serv->client)) == -1)
		return ;
	run_put(serv->client, file, size);
	ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
	close(file);
}
