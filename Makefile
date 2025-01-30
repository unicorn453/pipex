CC = cc
CC_FLAGS = -Wall -Wextra -Werror -g

NAME = pipex

SRCS = pipex.c input_parsing.c \
		init_stacks_free.c \
		free_err_functions.c \
		input_parsing_helper.c \
		pipe_fork.c \

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(LIBFT_DIR)/ft_printf/ft_printf.a

OBJ = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re