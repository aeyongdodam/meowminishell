

CC = cc

SRC = main.c
SRC += lexer/lexer.c lexer/lexer_token.c lexer/lexer_env.c lexer/lexer_utils.c lexer/lexer_utils2.c
SRC += utils/error_utils.c utils/error.c utils/free.c utils/init.c utils/signal.c utils/utils.c
SRC += pipe.c heredoc.c
SRC += builtin/cd.c builtin/cd_utils.c builtin/echo.c builtin/pwd.c builtin/env.c builtin/export.c builtin/export_utils.c builtin/export_utils2.c builtin/unset.c builtin/exit.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR	= ./libft
LIBFT_LIB	= -L $(LIBFT_DIR) -lft

HEADER = -include ./minishell.h
CFLAGS = #-Wall -Wextra -Werror
CFLAGS = #-g3 -fsanitize=address
COMFILE_FLAGS = -lreadline -L /$(shell brew --prefix readline)/lib
OBJ_FLAGS = -I /$(shell brew --prefix readline)/include

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(HEADER) $(COMFILE_FLAGS) $(LIBFT_LIB) -o $@ $^ 

%.o: %.c
		$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
		make -C ${LIBFT_DIR} clean
		rm -f $(OBJ)

fclean:	clean
		make -C ${LIBFT_DIR} fclean
		rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re