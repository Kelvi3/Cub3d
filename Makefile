# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:04:35 by tcazenav          #+#    #+#              #
#    Updated: 2023/06/16 15:12:03 by lulaens          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = 	main.c \
		parse/copy_cube_and_map.c \
		parse/parse.c \
		parse/check_map.c \
		parse/parse_colors.c \
		free_utils.c

CC = gcc

CFLAGS = -ggdb

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft && echo "LIBFT COMPILED"
	##@make -C minilibx-linux -s && echo "MLX COMPILED"
	@$(CC) $(CFLAGS) $(OBJ) gnl/get_next_line.c libft/libft.a -o $(NAME) | echo "OBJ COMPILED"
## minilibx-linux/libmlx.a -Lminilibix_linux -lXext -lX11 -lm -lz 
clean:
	@rm -f $(OBJ) && echo "CLEAN OBJ"
	@make clean -C libft -s && echo "LIBFT CLEANED"
	@make clean -C minilibx-linux -s && echo "MINILIBX-LINUX CLEANED"

fclean: clean
		@rm -f $(NAME) && echo "CLEAN ALL"

re: fclean all

.PHONY : all clean fclean re
