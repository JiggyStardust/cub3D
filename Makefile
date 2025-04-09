# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:52:26 by hpirkola          #+#    #+#              #
#    Updated: 2025/04/08 15:50:46 by sniemela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET 			= \033[0;39m
ORANGE 			= \e[1m\e[38;5;202m
CYAN_BOLD 		= \033[1;96m
GREEN			= \033[1;92m
GREEN_UNDER		= \033[4;32m
YELLOW 			= \033[0;93m

OBJ_READY		= echo "📥 $(ORANGE)Compiled .o files!$(RESET)"
X_READY			= echo "🤖 $(GREEN)cub3d ready!$(RESET)"
CLEANING		= echo "💧 $(CYAN_BOLD)Cleaning...$(RESET)"
CLEANED			= echo "💧 $(CYAN_BOLD)Successfully cleaned object files!$(RESET)"
FCLEANING		= echo "🧼 $(CYAN_BOLD)Deep cleaning...$(RESET)"
FCLEANED		= echo "🧼 $(CYAN_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "💡 $(GREEN)Successfully rebuilt everything!$(RESET)"
CUB3D			= echo "🔗 $(YELLOW)Linking cub3D...$(RESET)"

NAME = cub3D
CFLAGS = -Wall -g #-Werror -Wextra
LDFLAGS = -lglfw -lm
CC = cc

SOURCES = main.c \
	drawing.c \
	draw_minimap_rays.c \
	hooks_bonus.c \
	image_handling_bonus.c \
	images_to_window_bonus.c \
	init_utils.c \
	moving_bonus.c \
	parsing.c \
	raycasting.c \
	terminate_n_free_bonus.c \
	utils.c \
	validate.c \
	map.c \
	textures_and_colors.c

SRCDIR = src
OBJDIR = obj
OBJS = $(SOURCES:%.c=$(OBJDIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a

INCLUDE = -I. -I$(LIBFT_DIR) -I$(MLX42_DIR)/include -I~/.brew/Cellar/glfw/3.3.8/include/

REQUIRED_PACKAGES = build-essential libx11-dev libglfw3 xorg-dev
CHECK_PACKAGES_CMD = dpkg -l | grep -E '$(subst $(space),|,$(REQUIRED_PACKAGES))'

all: check_packages $(NAME)

check_packages:
	@if ! $(CHECK_PACKAGES_CMD) > /dev/null; then \
		echo "$(CYAN_BOLD)Required packages not installed.$(RESET)"; \
		echo "\n\nPlease install: $(REQUIRED_PACKAGES)"; \
		exit 1; \
	fi

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	@$(CUB3D)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(LDFLAGS) -o $(NAME)
	@$(X_READY)

$(OBJDIR): $(MLX42_LIB) $(LIBFT)
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@$(OBJ_READY)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

$(MLX42_LIB): clone_MLX42
	@if [ ! -f "$(MLX42_LIB)" ]; then \
		echo "Building MLX42 library..."; \
		cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4; \
	else \
		echo "$(CYAN_BOLD)MLX42 library is up-to-date, skipping build.$(RESET)"; \
	fi

clone_MLX42:
	@if [ ! -d "$(MLX42_DIR)" ] || [ -z "$$(ls -A $(MLX42_DIR))" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	else \
		echo "$(CYAN_BOLD)MLX42 already exists, skipping clone.$(RESET)"; \
	fi

clean:
	@$(CLEANING)
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@rm -rf $(MLX42_DIR)/build
	@$(CLEANED)

fclean: clean
	@$(FCLEANING)
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -rf $(MLX42_DIR)
	@$(FCLEANED)

re: fclean all
	@$(REMAKE)

.PHONY: all clean fclean re check_packages
