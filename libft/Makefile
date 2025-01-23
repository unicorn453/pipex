# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 17:45:19 by kruseva           #+#    #+#              #
#    Updated: 2025/01/23 20:30:37 by kruseva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c \
       ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
       get_next_line/get_next_line_bonus.c \
       get_next_line/get_next_line_utils_bonus.c
       
OBJ = $(SRCS:.c=.o)

FT_PRINTF = ft_printf/ft_printf.a
FT_PRINTF_DIR = ft_printf
CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c libft.h get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(FT_PRINTF)
	ar rcs $@ $^

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

all: $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
