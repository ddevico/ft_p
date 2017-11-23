/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/23 09:50:41 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int				send_error(int client, char *msg)
{
	ft_putendl_fd(msg, client);
	return (-1);
}

static int		open_file(char *cmd, t_client *client)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
	{
		ft_printcolor("ERROR : open() file\n", 31);
		send_error(client->sock, "ERROR_FD");
	}
	else
		ft_putendl_fd("CLIENT_OK", client->sock);
	return (file);
}

static void		run_put_client(struct stat buf, int client, void *ptr, int file)
{
	char		*totsize;

	totsize = ft_itoa(buf.st_size);
	ft_putendl_fd(totsize, client);
	free(totsize);
	if (alert_message_client("SEND", client) < 1)
		return ;
	send(client, ptr, buf.st_size, 0);
	munmap(ptr, buf.st_size);
	close(file);
	if (alert_message_client("SUCCESS", client) == 1)
		ft_printcolor("SUCCESS\n", 32);
}

static void		get_put_client2(t_client *client, struct stat buff, void *ptr,
		int file)
{
	send_error(client->sock, "TEST_OK");
	run_put_client(buff, client->sock, ptr, file);
}

void			get_put_client(t_client *client)
{
	int			file;
	struct stat	buff;
	void		*ptr;

	if ((file = open_file(client->buff, client)) == -1)
		return ;
	if (alert_message_client("VERIF_FD", client->sock) < 1)
	{
		ft_printcolor("ERROR : can't create the file, already exists\n", 31);
		return ;
	}
	if ((fstat(file, &buff)) == -1)
	{
		ft_printcolor("ERROR : fstat()\n", 31);
		send_error(client->sock, "TEST_ERROR");
		return ;
	}
	if ((ptr = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_printcolor("ERROR : mmap()\n", 31);
		send_error(client->sock, "TEST_ERROR");
		return ;
	}
	get_put_client2(client, buff, ptr, file);
}
