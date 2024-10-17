NAME = minishell

CC = cc
LIBFT_DIR = ./libft
CFLAGS = -Wall -Werror -Wextra -I ./includes -I $(LIBFT_DIR) -g
SRC_DIR = ./sources
LIBFT = $(LIBFT_DIR)/libft.a
READ_LINE = -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
YELLOW = \033[0;33m

SRC =	$(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READ_LINE) -o $(NAME)
	@echo "[$(GREEN)SUCCESS$(RESET)] $(NAME) CREATED."


$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re