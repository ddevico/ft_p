/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_clt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/29 10:36:17 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int					lrm(char *buff)
{
	char			**path;

	path = ft_strsplit(buff, ' ');
	if (!path[1])
		ft_printcolor("ERROR: No path specified\n", 31);
	else if (unlink(path[1]) == 0)
		ft_printcolor("SUCCESS\n", 32);
	else
		ft_printcolor("ERROR: lrm\n", 31);
	return (1);
}
