/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 15:48:58 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int		get_file(char *cmd, int sock)
{
	char			*filename;
	int				file;

	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
		ft_putendl_fd("FILE_ERROR", sock);
	else
		ft_putendl_fd("FILE_OK", sock);
	return (file);
}

void	recv_file(int sock, int file, int totsize)
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

int		get_filesize(int sock)
{
	int		size;
	char	*line;

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

void		get_get_client(t_serv *serv)
{
	int		file;
	int		size;

	if ((file = get_file(serv->buff, serv->client)) == -1)
	{
		ft_putendl_fd("ERROR: open() failed", serv->client);
		return ;
	}
	if ((size = get_filesize(serv->client)) == -1)
	{
		ft_putendl_fd("ERROR: size failed", serv->client);
		return ;
	}
	recv_file(serv->client, file, size);
	ft_putendl_fd("\nSUCCESS", serv->client);
	close(file);
}

void					get_put_client(t_serv *serv)
{
	char				**file;
	struct stat 		buff[1024];
	int					fd;
	void				*ptr;

	file = ft_strsplit(serv->buff, ' ');
	if ((fd = open(file[1], O_RDONLY)) < 0)
	{
		ft_putendl_fd("ERROR: open() failed", serv->client);
		return ;
	}
	if ((serv->ret = fstat(fd, buff)) == -1)
	{
		ft_putendl_fd("ERROR: fstat failed", serv->client);
		return ;
	}
	if ((ptr = mmap(NULL, buff->st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("ERROR: mmap failed", serv->client);
		return ;
	}
	ft_putendl_fd(ptr, serv->client);
	ft_putendl_fd("SUCCESS", serv->client);
}