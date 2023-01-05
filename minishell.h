
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <fcntl.h>

# include "./libft/libft.h"

# define ROOT 0
# define WORD 1
# define PIPE 2
# define REDI 3
# define DOUBLE_QUOTES 4
# define SINGLE_QUOTES 5
# define HERE 6

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*str;
	int				flag;
}	t_token;

typedef struct s_node
{
	t_token			*token;
	struct s_node	*left_child;
	struct s_node	*right_child;
}	t_node;

typedef struct s_tree
{
	struct s_node	*root;
	int				pipe_cnt;
	int				ridi_cnt;
	int				heredoc_cnt;
	int				space;
	int				pipe;
	int				double_quote;
	int				single_quote;
}	t_tree;

typedef struct s_pipe{
	int	**fd;
	int	pipe_cnt;
}	t_pipe;

typedef struct s_envnode
{
	struct s_envnode	*prev;
	struct s_envnode	*next;
	char				*key;
	char				*value;
}	t_envnode;

//signal.c
void	signal_handler(int sig);
void	signal_handler2(int sig);
void	set_signal_handler(int flag);
void	set_terminal(void);

//init.c
t_token	*init_token(void);
t_node	*init_node(void);
t_tree	*init_tree(void);
t_envnode	*init_env(char **envp);
t_envnode	*init_envnode(t_envnode	**head, char	*str);

//lexer.c
void	save_token(t_node *node, char *str, int flag);
t_node	*pipe_token(t_node *node, char *str, t_tree *tree);
int		redi_token(t_node *node, char *line, char *str, t_tree *tree);
t_tree	*lexer(char	*line);

//lexer_utils
int		get_type(char *line);
char	*str_one_join(char *s1, char c);
char	*re_str(char *str);

//pipe.c
void	main_pipe(t_tree *tree, char *envp[]);

//utils
void	prt_tree(t_node *node, int le, int ri);

//builtin
void builtin_echo(char **command);

#endif
