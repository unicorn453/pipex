# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:47:10 by kruseva           #+#    #+#              #
#    Updated: 2025/01/18 21:48:02 by kruseva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC_FLAGS = -Wall -Werror -Wextra

NAME = ft_printf.a 

SRC_FILES = ft_putnbr.c conversion.c helper_functions.c ft_printf.c hexadecimal.c

OBJ_FILES = $(SRC_FILES:%.c=%.o)


%.o: %.c 
	$(CC) $(CC_FLAGS) -c $< -o $@ 


$(NAME): $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)


all: $(NAME)


clean:
	rm -f $(OBJ_FILES) 

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
