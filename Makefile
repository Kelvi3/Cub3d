# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:04:35 by tcazenav          #+#    #+#              #
#    Updated: 2023/03/01 18:10:09 by tcazenav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = ./src/main.c\
	  ./src/error.c\
	  ./src/get_next_line.c\
	  ./src/get_next_line_utils.c\
	  ./src/utils.c\
	  ./src/error_bis.c\
	  ./src/so_long.c\
	  ./src/initialize_img.c\
	  ./src/key_event.c\
	  ./src/save_map.c\
	  ./src/moov_player.c\
	  ./src/free_all.c

CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -g3 

OBJ = $(SRC:.c=.o)

%.o: %.c
	clang $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		make -C mlx_linux -s
		clang $(OBJ) mlx_linux/libmlx.a -Lmlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
		rm -f $(OBJ) $(OBJ_BONUS)
		make clean -C mlx_linux -s

fclean: clean
		rm -f $(NAME) 

re: fclean all

.PHONY : all clean fclean re
