# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:04:35 by tcazenav          #+#    #+#              #
#    Updated: 2023/07/07 12:33:26 by lulaens          ###   ########.fr        #
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
		raycasting/calculate_raycasting.c \
		moov_player.c \

CC = gcc

CFLAGS = -I/usr/include -O3 -Wall -Werror -Wextra -g

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	#@make -C MLX42
	@$(CC) $(CFLAGS) $(OBJ) gnl/get_next_line.c libft/libft.a MLX42/build/libmlx42.a -I include -ldl -pthread -lglfw -lm -o $(NAME)

clean:
	@rm -f $(OBJ) && echo "CLEAN OBJ"
	@make clean -C libft -s && echo "LIBFT CLEANED"
	#@make clean -C minilibx-linux -s && echo "MINILIBX-LINUX CLEANED"

fclean: clean
			@rm -f $(NAME) && echo "CLEAN ALL"

re: fclean all

.PHONY : all clean fclean re


