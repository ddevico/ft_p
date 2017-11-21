/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 15:00:50 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

void		ft_printcolor(char *str, int color)
{
	ft_putstr("\033[");
	ft_putnbr(color);
	ft_putstr("m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}

int 		print_error(char *str) {
	ft_printcolor(str, 31);
	return (-1);
}

int			server_login(int sock)
{
	int		ret;
	char	buff[1024];
	char	*line;
	int		fd;

	ret = 0;
	line = NULL;
	buff[0] = '\0';
	ret = recv(sock, buff, 1023, 0);
	if (ft_strequ(buff, "admin:admin") < 1)
	{
		send(sock, "WRONG_PASS", 10, 0);
		return (-1);
	}
	send(sock, "OK", 10, 0);
	return (0);
}

int			alert_message(char *str, int fd)
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
