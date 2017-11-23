/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddeico <ddeico@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:02:15 by ddeico            #+#    #+#             */
/*   Updated: 2017/11/23 11:34:00 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
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
# define BUFF_SIZE2 256
# define MAX_FD_NBR 10

typedef struct			s_serv
{
	int					client;
	int					port;
	pid_t				pid;
	char				pwd[1024];
	int					sock;
	char				*buff;
	char				tmp[1];
	int					read;
	int					read2;
	int					counter;
	int					fd;
	int					ret;
}						t_serv;

typedef struct			s_client
{
	int					sock;
	char				*buff;
	char				tmp[1];
	int					i;
	int					read;
	int					read2;
	int					fd;
	int					ret;
	char				**tab;
}						t_client;

int						gest_serveur(t_serv *serv);

void					get_pwd(int client);
void					get_ls(int client);
void					get_cd(char *command, t_serv *serv);

void					get_mkdir(char *command, t_serv *serv);
void					get_rmdir(char *command, t_serv *serv);
void					get_rm(char *command, t_serv *serv);


void					get_put(t_serv *serv);

void					get_get(t_serv *serv);

int						ft_get_next_line(int const fd, char **line);

int						gest_client(t_client *client, char *login);
void					get_get_client(t_client *client);
void					get_put_client(t_client *client);

int						alert_message(char *str, int fd);
int						alert_message_put(char *str, int fd);
int						server_login(int sock);
int						print_error(char *str);
void					ft_printcolor(char *str, int color);

int						alert_message_client(char *str, int fd);

int						lpwd();
int						lcd(char *buff);
int						lls();
int						lmkdir(char *buff);
int						lrmdir(char *buff);

#endif
