# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 09:31:23 by hpirkola          #+#    #+#              #
#    Updated: 2025/02/26 16:19:48 by hpirkola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = ./ft_isalpha.c \
		  ./ft_isdigit.c \
		  ./ft_isalnum.c \
		  ./ft_isascii.c \
		  ./ft_isprint.c \
		  ./ft_strlen.c \
		  ./ft_memset.c \
		  ./ft_bzero.c \
		  ./ft_memcpy.c \
		  ./ft_memmove.c \
		  ./ft_strlcpy.c \
		  ./ft_strlcat.c \
		  ./ft_toupper.c \
		  ./ft_tolower.c \
		  ./ft_strchr.c \
		  ./ft_strrchr.c \
		  ./ft_strncmp.c \
		  ./ft_memchr.c \
		  ./ft_memcmp.c \
		  ./ft_strnstr.c \
		  ./ft_atoi.c \
		  ./ft_calloc.c \
		  ./ft_strdup.c \
		  ./ft_putchar_fd.c \
		  ./ft_putstr_fd.c \
		  ./ft_putendl_fd.c \
		  ./ft_putnbr_fd.c \
		  ./ft_split.c \
		  ./ft_strjoin.c \
		  ./ft_strmapi.c \
		  ./ft_striteri.c \
		  ./ft_substr.c \
		  ./ft_strtrim.c \
		  ./ft_itoa.c \
		  ./get_next_line/get_next_line.c \
		  ./get_next_line/get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

BONUS_SRCS = ./ft_lstnew_bonus.c \
			 ./ft_lstadd_front_bonus.c \
			 ./ft_lstlast_bonus.c \
			 ./ft_lstsize_bonus.c \
			 ./ft_lstadd_back_bonus.c \
			 ./ft_lstdelone_bonus.c \
			 ./ft_lstclear_bonus.c \
			 ./ft_lstiter_bonus.c \
			 ./ft_lstmap_bonus.c \

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

bonus: .bonus 

.bonus: $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)
	@touch .bonus

clean:
	@rm -f $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f .bonus

re: fclean all

.PHONY: all clean fclean re bonus
