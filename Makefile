# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:04:35 by tcazenav          #+#    #+#              #
#    Updated: 2023/06/21 10:08:04 by lulaens          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = 	main.c \
		parse/check_map.c \
		parse/colors_int.c \
		parse/colors_string.c \
		parse/copy_cube_and_map.c \
		parse/extension.c \
		parse/in_map.c \
		parse/textures.c \
		parse/textures_path.c \
		parse/utils_parse.c \
		parse/parse.c \
		free_utils.c \
		raycasting/raycasting.c \

CC = clang

CFLAGS = -I/usr/include -O3 -Wall -Werror -Wextra -g

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@make -C minilibx-linux

	@$(CC) $(CFLAGS) $(OBJ) gnl/get_next_line.c libft/libft.a -o $(NAME) | echo "OBJ COMPILED"
	@make -C libft && echo "LIBFT COMPILED"
	@make -C ./minilibx-linux && echo "MLX COMPILED"
	@$(CC) $(CFLAGS) $(OBJ) gnl/get_next_line.c libft/libft.a minilibx-linux/libmlx.a -Lminilibx-Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) | echo "OBJ COMPILED"

clean:
	@rm -f $(OBJ) && echo "CLEAN OBJ"
	@make clean -C libft -s && echo "LIBFT CLEANED"
	@make clean -C minilibx-linux -s && echo "MINILIBX-LINUX CLEANED"

fclean: clean
			@rm -f $(NAME) && echo "CLEAN ALL"

re: fclean all

.PHONY : all clean fclean re


