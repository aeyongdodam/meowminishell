# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 01:02:46 by mkwon             #+#    #+#              #
#    Updated: 2023/01/15 01:20:09 by sohlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

SRC = main.c
SRC += lexer/lexer.c lexer/lexer_token.c lexer/lexer_env.c lexer/lexer_utils.c lexer/lexer_utils2.c
SRC += utils/error_utils.c utils/error.c utils/free.c utils/init.c utils/signal.c utils/utils.c
SRC += builtin/cd.c builtin/cd_utils.c builtin/echo.c builtin/pwd.c builtin/env.c builtin/export.c builtin/export_utils.c builtin/export_utils2.c builtin/unset.c builtin/exit.c
SRC += pipe_utils/free_function.c pipe_utils/pipe_connect_fd.c pipe_utils/child_and_parent_utils.c \
pipe_utils/close_all_pipe.c pipe_utils/find_path.c pipe_utils/get_command.c \
pipe_utils/handle_error.c pipe_utils/pipe_builtin_utils.c \
pipe_utils/pipe_connect.c \
pipe_utils/redi_command_utils.c
SRC += pipe.c heredoc.c heredoc_utils.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR	= ./libft
LIBFT_LIB	= -L $(LIBFT_DIR) -lft

HEADER = -include ./minishell.h
CFLAGS = -Wall -Werror -Wextra
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
