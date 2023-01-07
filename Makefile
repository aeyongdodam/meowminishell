

CC = cc
SRC = main.c signal.c init.c error.c
SRC += lexer/lexer.c lexer/lexer_token.c lexer/lexer_env.c lexer/lexer_utils.c
SRC += pipe.c
SRC += builtin/echo.c builtin/cd.c builtin/pwd.c
SRC += utils.c
OBJ = $(SRC:.c=.o)
HEADER = -include ./minishell.h

# CFLAGS = #-Wall -Wextra -Werror
CFLAGS = #-g3 -fsanitize=address
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