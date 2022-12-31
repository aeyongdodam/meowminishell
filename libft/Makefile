# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 11:25:47 by mkwon             #+#    #+#              #
#    Updated: 2022/05/21 16:43:15 by mkwon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = ft_atoi.c	\
		ft_isdigit.c \
		ft_memmove.c \
		ft_split.c \
		ft_strlcpy.c \
		ft_strtrim.c \
		ft_bzero.c \
		ft_isprint.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlen.c \
		ft_substr.c \
		ft_calloc.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_strdup.c \
		ft_strmapi.c \
		ft_tolower.c \
		ft_isalnum.c \
		ft_memchr.c \
		ft_putendl_fd.c \
		ft_striteri.c \
		ft_strncmp.c \
		ft_toupper.c \
		ft_isalpha.c \
		ft_memcmp.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strnstr.c \
		ft_isascii.c \
		ft_memcpy.c \
		ft_putstr_fd.c \
		ft_strlcat.c \
		ft_strrchr.c

OBJ = $(SRC:.c=.o)

HEAD = libft.h
NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

.c .o : $(SRC)
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ)
	ar -rcus $@  $^

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

