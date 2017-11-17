# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/03 12:02:00 by ddevico           #+#    #+#              #
#    Updated: 2017/11/17 08:31:08 by davydevico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serveur

SRC_DIR	= ./serveur_src

SRC = 	serveur.c \
		gest_client.c \
		get_cmd.c \
		get_get.c \
		get_put.c \
		utils.c \
		ft_get_next_line.c \

VPATH	= $(SRC_DIR)

O_DIR	= ./obj
OBJ		= $(addprefix $(O_DIR)/,$(SRC:.c=.o))

WFLAGS = #-Wall -Werror -Wextra

CC = gcc

HEADERS = -I includes/

I_LIBFT = -I libft/includes/

I_PRINTF = libft/ft_printf/libftprintf.a

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME)

$(NAME): obj $(OBJ)
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
	@$(CC) $(WFLAGS) -o $@ $(OBJ) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\033[1;34mwoody\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"
	@echo "\n\033[32m==> SUCCESS !\033[0m\n"

obj/%.o: %.c
	@$(CC) $(WFLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

obj:
		@mkdir -p obj/

clean:
	@echo "\n\033[35m==> CLEANING in progress ...\033[0m\n"
	@make clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "\n\033[32m==> SUCCESS !\033[0m\n"

re: fclean all

norminette:
	@echo "\n"----------------------- NORMINETTE LIBFT --------------------------"\n"
	@norminette libft/*.c libft/includes/*.h
	@echo "\n"----------------------- NORMINETTE MALLOC -------------------------"\n"
	@norminette serveur/*.c client/*.c inc/ft_p.h
	@echo "\n"--------------------------- END -----------------------------------"\n"

.PHONY: re fclean clean all norminette
