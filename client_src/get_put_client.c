/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 09:24:01 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int		print_error(int client, char *msg)
{
	ft_putendl_fd(msg, client);
	return (-1);
}

static int		open_file(char *cmd, int client)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
	{
		ft_putendl("ERROR : open() file");
		print_error(client, "FILE_ERROR");
	}
	else
		print_error(client, "FILE_CLT_OK");
	return (file);
}

static void		run_put_client(struct stat buf, int client, void *ptr, int file)
{
	char		*totsize;

	totsize = ft_itoa(buf.st_size);
	ft_putendl_fd(totsize, client);
	free(totsize);
	if (alert_message_client("GO_SEND", client) < 1)
		return ;
	send(client, ptr, buf.st_size, 0);
	munmap(ptr, buf.st_size);
	close(file);
	if (alert_message_client("SUCCESS", client) == 1)
		ft_putendl("SUCCESS");
}

void			get_put_client(t_client *client)
{
	int			file;
	struct stat	buff;
	void		*ptr;

	if ((file = open_file(client->buff, client->sock)) == -1)
		return ;
	if (alert_message_client("FILE_OK", client->sock) < 1)
	{
		ft_putendl("ERROR : can't create the file, already exists");
		return ;
	}
	if ((fstat(file, &buff)) == -1)
	{
		ft_putendl("ERROR : fstat()");
		return ;
	}
	if ((ptr = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl("ERROR : mmap()");
		return ;
	}
	run_put_client(buff, client->sock, ptr, file);
}
