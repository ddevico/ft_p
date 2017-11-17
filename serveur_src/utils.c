/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/17 10:51:36 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void		ft_putendl_fd(char const *s, int fd)
{
	int		index;

	index = 0;
	while (s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
	ft_putchar_fd('\n', fd);
}

void		ft_putendl_fd_backslach(char const *s, int fd)
{
	int		index;

	index = 0;
	while (s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
}

void		add_space(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
			s[i] = ' ';
	}
}
