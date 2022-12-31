

CC = cc
SRC = main.c signal.c init.c lexer.c pipe.c
OBJ = $(SRC:.c=.o)
HEADER = -include ./minishell.h

CFLAGS = #-Wall -Wextra -Werror
COMFILE_FLAGS = -lreadline -L /$(shell brew --prefix readline)/lib
OBJ_FLAGS = -I /$(shell brew --prefix readline)/include

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(HEADER) $(COMFILE_FLAGS)  -o $@ $^ ./libft/libft.a

%.o: %.c
		$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re