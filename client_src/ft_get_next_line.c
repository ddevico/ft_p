/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 16:26:46 by rfrey             #+#    #+#             */
/*   Updated: 2017/11/21 17:01:25 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../inc/ft_p.h"

static char		*ft_get_join(char *s1, char *s2)
{
	char		*dst;

	if (s1 == NULL)
	{
		s1 = ft_strnew(1);
		ft_bzero(s1, sizeof(s1));
		s1 = "";
	}
	if (!s1 || !s2)
		return ((char *)0);
	dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return ((char *)0);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	return (dst);
}

static int		ft_read(int fd, char **tmp)
{
	int			ret;
	char		buf[BUF_SIZE + 1];

	if (*tmp != NULL && ft_strchr(*tmp, '\n'))
		return (1);
	ft_bzero(buf, sizeof(buf));
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		*tmp = ft_get_join(*tmp, buf);
		if (*tmp == NULL)
			return (-1);
		if (ft_strchr(*tmp, '\n') != NULL)
			break ;
		ft_bzero(buf, sizeof(buf));
	}
	return (ret <= 0 ? ret : 1);
}

static void		ft_str(char **line, char **tmp, int *ret)
{
	char		*ptr;

	if (*tmp != NULL && ft_strlen(*tmp) > 0)
	{
		*ret = 1;
		ptr = ft_strchr(*tmp, '\n');
		if (ptr == NULL)
		{
			*line = *tmp;
			*tmp = NULL;
		}
		else
		{
			*line = *tmp;
			*ptr = '\0';
			*tmp = ft_strdup(ptr + 1);
		}
	}
	return ;
}

int				ft_get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*current = NULL;

	if (line == NULL)
		return (-1);
	*line = NULL;
	ret = ft_read(fd, &current);
	if (ret < 0)
		return (-1);
	ft_str(line, &current, &ret);
	return (ret);
}
