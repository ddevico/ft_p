/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/20 17:17:32 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int						gest_client(t_client *client)
{
	int					r;

	client->buff[client->read - 1] = '\0';
	write(client->sock, client->buff, client->read);
	if (ft_strncmp("get ", client->buff, 4) == 0)
		get_get_client(client);
	else if (ft_strncmp("put ", client->buff, 4) == 0)
		get_put_client(client);
	else if (ft_strcmp("quit", client->buff) == 0)
	{
		ft_putendl("\nSUCCESS");
		exit(0);
	}
	else
	{
		while ((r = read(client->sock, client->buff, 1)) > 0 && client->buff[0] != '\0')
		{
			client->buff[r] = '\0';
			write(1, client->buff, r);
		}
	}
	ft_printf("ft_p> ");
	return (0);
}
