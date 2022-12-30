CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
SRCS = ft_isascii.c \
	   ft_memcpy.c \
	   ft_putstr_fd.c \
	   ft_strlcat.c \
	   ft_strrchr.c \
	   ft_atoi.c \
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
	   ft_strnstr.c
BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

ifdef BONUS_FLAG
		OBJS_SELECT = $(OBJS) $(BONUS_OBJS)
else
		OBJS_SELECT = $(OBJS)
endif

all : $(NAME)
$(NAME) : $(OBJS_SELECT)
			ar rcs $(NAME) $(OBJS_SELECT)
%.o : %.c
	$(CC) $(CFLAGS) -c $<

bonus : 
	make BONUS_FLAG=1
clean :
		rm -f $(OBJS) $(BONUS_OBJS)
fclean : clean
		rm -f $(NAME)
re : 
	make fclean 
	 make all
.PHONY : all clean fclean re bonus
