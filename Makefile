# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:04:35 by tcazenav          #+#    #+#              #
#    Updated: 2023/06/14 10:36:44 by tcazenav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = main.c \

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

%.o: %.c
	@clang -g3 $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft -s && echo "LIBFT COMPILED"
	@make -C minilibx-linux && echo "MLX COMPILED"
	@clang $(CFLAGS) $(OBJ) gnl/get_next_line.c libft/libft.a minilibx-linux/libmlx.a -Lminilibix_linux -lXext -lX11 -lm -lz -o $(NAME) | echo "OBJ COMPILED"

clean:
	@rm -f $(OBJ) && echo "CLEAN OBJ"
	@make clean -C libft -s && echo "LIBFT CLEANED"
	@make clean -C minilibx-linux -s && echo "MINILIBX-LINUX CLEANED"

fclean: clean
		@rm -f $(NAME) && echo "CLEAN ALL"

re: fclean all

.PHONY : all clean fclean re
