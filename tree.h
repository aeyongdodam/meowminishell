#ifndef TREE_H
#define TREE_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
#include <termios.h>

# include "./libft/libft.h"

# define ROOT 0
# define WORD 1
# define PIPE 2
# define REDI 3
# define T_DOUBLE_QUOTES 4
# define T_SINGLE_QUOTES 5

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*str;
}	t_token;

typedef struct s_node
{
	t_token			*token;
	int				flag;
	struct s_node	*left_child;
	struct s_node	*right_child;
}	t_node;


#endif
