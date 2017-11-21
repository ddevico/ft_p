/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:16:17 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 17:11:18 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

int		ft_strequ(char const *s1, char const *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (*s1++ && *s2++)
	{
		if (*s1 != *s2)
			return (0);
	}
	return (1);
}
