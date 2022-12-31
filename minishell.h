
#ifndef MINISHELL_H
# define MINISHELL_H

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
# define DOUBLE_QUOTES 4
# define SINGLE_QUOTES 5

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

typedef struct s_tree
{
	struct s_node	*root;
	int				pipe_cnt;
	int				ridi_cnt;
}	t_tree;

//signal.c
void	signal_handler(int sig);
void	signal_handler2(int sig);
void	set_signal_handler(int flag);

//init.c
t_token  *init_token(void);
t_node	*init_node(void);
t_tree	*init_tree(void);

//lexer.c
char	*re_str(char *str);
char	*str_one_join(char *s1, char c);
void	save_token(t_node *node, char *str, int flag);
void	prt_tree(t_node *node,int le, int ri);

#endif
