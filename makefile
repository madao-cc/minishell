# Standard
NAME	=	sh

# Compiler and Flags
CC		=	cc
LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a
READ_LINE	=	-lreadline

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
YELLOW = \033[0;33m

# Extras


# Silent Compilation unless VERBOSE is set
ifeq ($(VERBOSE), 1)
    ECHO =
else
    ECHO = @
endif

# Source files
SRCS	=	sh2.c	\
		signals.c
		

# Object files
OBJS	=	$(SRCS:.c=.o)

# Builld Rules
all: $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READ_LINE) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean:		clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re:	fclean all

start: all

.PHONY: start all clean fclean re
	