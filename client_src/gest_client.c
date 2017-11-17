/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 15:51:49 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int						gest_client(t_serv *serv)
{
	int					r;

	serv->buff[serv->read - 1] = '\0';
	write(serv->sock, serv->buff, serv->read);
	if (!ft_strcmp("ls", serv->buff) || !ft_strcmp("pwd", serv->buff)
	|| !ft_strcmp("cd", serv->buff))
	{
		while ((r = read(serv->sock, serv->buff, 1)) > 0 && serv->buff[0] != '\0')
		{
			serv->buff[r] = '\0';
			write(1, serv->buff, r);
		}
	}
	else if (ft_strncmp("get ", serv->buff, 4) == 0)
		get_get_client(serv);
	else if (ft_strncmp("put ", serv->buff, 4) == 0)
		get_put_client(serv);
	else if (ft_strcmp("quit", serv->buff) == 0)
	{
		ft_putendl("\nSUCCESS");
		exit(0);
	}
	ft_printf("ft_p> ");
	return (0);
}
