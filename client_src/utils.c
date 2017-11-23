/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/23 09:51:08 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void			ft_printcolor(char *str, int color)
{
	ft_putstr("\033[");
	ft_putnbr(color);
	ft_putstr("m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}

int				print_error(char *str)
{
	ft_printf("%s", str);
	return (-1);
}

int				alert_message_client(char *str, int fd)
{
	char	*input;
	int		ret;

	input = NULL;
	if (ft_get_next_line(fd, &input) == -1)
		return (-1);
	ret = ft_strequ(input, str);
	free(input);
	return (ret);
}
