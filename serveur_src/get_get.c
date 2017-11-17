/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 11:41:02 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void					get_get(t_serv *serv)
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
