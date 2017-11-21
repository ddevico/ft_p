# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#              #
#    Updated: 2017/11/21 08:34:28 by davydevico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S	= serveur
NAME_C	= client

SRC_DIR_S	= ./serveur_src
SRC_DIR_C	= ./client_src

SRC_S = serveur.c \
		gest_client.c \
		get_cmd.c \
		get_get.c \
		get_put.c \
		utils.c \
		ft_get_next_line.c \

SRC_C =	client.c \
		gest_client.c \
		ft_get_next_line.c \
		get_put_client.c \
		get_get_client.c \
		utils.c \


O_DIR_S	= ./obj/nm
OBJ_S		= $(addprefix $(SRC_DIR_S)/,$(SRC_S:.c=.o))
O_DIR_C	= ./obj/otool
OBJ_C		= $(addprefix $(SRC_DIR_C)/,$(SRC_C:.c=.o))

CC = gcc

CFLAGS = #-Wall -Werror -Wextra

HEADERS = -I inc/

I_LIBFT = -I libft/inc/

I_PRINTF = libft/ft_printf/libftprintf.a

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME_S) $(NAME_C)

$(NAME_S): serveur

$(NAME_C): client

serveur: $(OBJ_S)
	@echo "\n";
	@echo "$(CG)     ███████╗████████╗       ██████╗$(CE)";
	@echo "$(CG)     ██╔════╝╚══██╔══╝       ██╔══██╗$(CE)";
	@echo "$(CG)     █████╗     ██║          ██████╔╝$(CE)";
	@echo "$(CG)     ██╔══╝     ██║          ██╔═══╝$(CE)";
	@echo "$(CG)     ██║        ██║ ███████╗ ██║$(CE)";
	@echo "$(CG)     ╚═╝        ╚═╝ ╚══════╝ ╚═╝$(CE)";
	@echo "\n";
	@echo "\n\033[31m==> COMPILING in progress ...\033[0m\n"
	@make -C libft
	@$(CC) $(WFLAGS) -o $@ $(OBJ_S) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\n\033[32m==> SUCCESS !\033[0m\n"

client: $(OBJ_C)
		@echo "\n\033[31m==> COMPILING in progress ...\033[0m\n"
		@make -C libft
		@$(CC) $(WFLAGS) $(O_NM_NO_MAIN) $(HEADERS) -o $@ $(OBJ_C) $(LIBFT) $(I_PRINTF)
		@echo "\n\033[32m==> SUCCESS !\033[0m\n"

obj/%.o: %.c
	@$(CC) $(WFLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

res:
	@mkdir -p res/
	@cat /usr/include/mach-o/loader.h > res/loader.h
	@cat /usr/include/mach-o/nlist.h > res/nlist.h
	@cat /usr/include/mach-o/fat.h > res/fat.h
	@cat /usr/include/ar.h > res/ar.h
	@cat /usr/include/mach-o/ranlib.h > res/ranlib.h

clean:
	@echo "\n\033[35m==> CLEANING in progress ...\033[0m\n"
	@rm -rf $(OBJ_S) $(OBJ_C) $(NAME_S) $(NAME_C)

fclean: clean
	@make fclean -C libft
	@echo "\033[35m==> CLEANING test files ...\033[0m\n"
	@rm -rf ./obj

re: fclean all

norminette:
	@echo "\n"----------------------- NORMINETTE LIBFT --------------------------"\n"
	@norminette libft/lib/*.c libft/ft_printf/src/*.c libft/ft_printf/lib/*.c libft/inc/*.h
	@echo "\n"----------------------- NORMINETTE NM -------------------------"\n"
	@norminette src/nm/*.c src/otool/*.c inc/nm_otool.h
	@echo "\n"--------------------------- END -----------------------------------"\n"

.PHONY: re fclean clean all norminette
