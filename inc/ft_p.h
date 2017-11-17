/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddeico <ddeico@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:15 by ddeico            #+#    #+#             */
/*   Updated: 2017/11/17 15:49:30 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dirent.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
# define BUF_SIZE 10

typedef struct	s_serv
{
	int			client;
	int			port;
	pid_t		pid;
	char		pwd[1024];
	int			sock;
	char		buff[1024];
	char		tmp[1];
	int			read;
	int			read2;
	int			counter;
	int			fd;
	int			ret;
}				t_serv;

int				gest_serveur(t_serv *serv);

void			get_pwd(int client);
void    		get_ls(int client);
void			get_cd(char *command, t_serv *serv);
void			get_put(t_serv *serv);
void			get_get(t_serv *serv);

int				ft_get_next_line(int const fd, char **line);

void			ft_putendl_fd_backslach(char const *s, int fd);
void			add_space(char *s);
void			ft_putcolor(char *str, char *color, int fd);

int				gest_client(t_serv *serv);
void			get_get_client(t_serv *serv);
void			get_put_client(t_serv *serv);

#endif
