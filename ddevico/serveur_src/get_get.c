/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/22 09:46:51 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int				send_error(int client, char *msg)
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
		ft_putendl_fd("ERROR_FD", client);
	else
		ft_putendl_fd("SERVER_OK", client);
	return (file);
}

static void		run_get(t_serv *serv, struct stat buff, void *ptr)
{
	char		*size;

	size = ft_itoa(buff.st_size);
	ft_putendl_fd(size, serv->client);
	free(size);
	if (alert_message("SEND", serv->client) < 1)
		return ;
	send(serv->client, ptr, buff.st_size, 0);
	munmap(ptr, buff.st_size);
}

void			get_get(t_serv *serv)
{
	int			file;
	struct stat	buff;
	void		*ptr;

	if ((file = open_file(serv->buff, serv->client)) == -1)
		return ;
	if (alert_message("VERIF_FD", serv->client) < 1)
		return ;
	if ((fstat(file, &buff)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", serv->client);
		return ;
	}
	if ((ptr = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", serv->client);
		return ;
	}
	ft_putendl_fd("TEST_OK", serv->client);
	run_get(serv, buff, ptr);
	close(file);
	if (alert_message("SUCCESS", serv->client) == 1)
		ft_putendl_fd("\033[32mSUCCESS\033[0m", serv->client);
}
