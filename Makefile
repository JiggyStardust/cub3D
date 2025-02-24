# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:52:26 by hpirkola          #+#    #+#              #
#    Updated: 2025/02/24 16:23:53 by hpirkola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = ./src/main.c ./src/parsing.c ./src/utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g
libft_dir := ./library/libft
INCLUDES = -I./includes -I$(libft_dir)
libft := $(libft_dir)/libft.a

all: $(NAME)

$(libft):
	make -C $(libft_dir)

$(NAME): $(libft) $(OBJ)
	cc $(CFLAGS) $(INCLUDES) $(OBJ) $(libft) -o $@

%.o : %.c
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(libft_dir) clean

fclean: clean
	rm -f $(NAME)
	make -C $(libft_dir) fclean

re: fclean all

.PHONY: all clean fclean re
