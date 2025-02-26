# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:52:26 by hpirkola          #+#    #+#              #
#    Updated: 2025/02/26 16:21:06 by hpirkola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

GREEN =  \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
ORANGE = \e[1m\e[38;5;202m
RESET = \033[0;39m

COMPILED = echo "🗃️  $(ORANGE)Files compiled!$(RESET)"
READY = echo "🎮 $(GREEN) Ready to play!"
CLEANING = echo "🫧 $(BLUE)Cleaning files...$(RESET)"
CLEANED = echo "🫧 $(BLUE)All object files cleaned!$(RESET)"
FCLEANING = echo "🧽 $(PURPLE)Deep cleaning files...$(RESET)"
FCLEANED = echo "🧽 $(PURPLE)All cleaned!$(RESET)"
REDO = echo "🛠️ $(RED)Program rebuilt!$(RESET)"

SRC = ./src/main.c ./src/parsing.c ./src/utils.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g
libft_dir := ./library/libft
INCLUDES = -I./includes -I$(libft_dir)
libft := $(libft_dir)/libft.a

all: $(NAME)

$(libft):
	@make -C $(libft_dir)

$(NAME): $(libft) $(OBJ)
	@cc $(CFLAGS) $(INCLUDES) $(OBJ) $(libft) -o $@
	@$(COMPILED)
	@$(READY)

%.o : %.c
	@cc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(libft_dir) clean
	@$(CLEANING)
	@$(CLEANED)

fclean: clean
	@rm -f $(NAME)
	@make -C $(libft_dir) fclean
	@$(FCLEANING)
	@$(FCLEANED)

re: fclean all
	@$(REDO)

.PHONY: all clean fclean re
