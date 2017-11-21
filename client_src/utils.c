/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#             */
/*   Updated: 2017/11/21 08:38:52 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_p.h"

int			alert_message_client(char *str, int fd)
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
