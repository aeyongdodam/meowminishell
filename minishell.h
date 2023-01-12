
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
# define QUOTE_D 4
# define QUOTE_S 5
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
	struct s_envnode	*env;
	int				pipe_cnt;
	int				ridi_cnt;
	int				heredoc_cnt;
	int				space;
	int				pipe;
	int				redi;
}	t_tree;

typedef struct s_pipe{
	int	**fd;
	int	cd_cnt;
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
t_envnode	*init_env(char **envp, t_tree *tree);
t_envnode	*init_envnode(t_envnode	**head, char *str);

//lexer.c
int		get_type(char *line);
t_tree	*lexer(char	*line, t_envnode *envnode);

//lexer_token.c
void	save_token(t_node *node, char *str, int flag);
void	word_token(t_node *node, char **str, t_tree *tree);
t_node	*pipe_token(t_node *node, char **str, t_tree *tree);
void	redi_token(t_node *node, char **line, char **str, t_tree *tree);
void	check_quote(t_node *node, char **line, char **str, t_tree *tree);

//lexer_env.c
char	*change_env(char *str2, t_envnode *envnode);
void	check_dallor(t_node *node, char **line, char **str, t_tree *tree);

//lexer_utils.c
char	*str_one_join(char *s1, char c, t_tree *tree, int flag);
char	*re_str(char *str);
void	set_variable(t_tree *tree, int space, int pipe, int redi);
void	set_lexer(t_node **node, t_tree **tree, char **stre, t_envnode *envnode);
void	double_redi(t_node *node, char **line, char **str, t_tree *tree);

//error.c
void	prt_error(int flag, char *str);
int		check_pipe(t_node *node, int flag);
int		error_pipe(t_node *node);
int		error_redi(t_node *node);
int		find_error(t_tree *tree, char *line);

//pipe.c
void	main_pipe(t_tree *tree, t_envnode *envnode, char **envp);

//utils
void	prt_tree(t_node *node, int le, int ri);
int		input_exit(t_tree *tree);
void	prt_exit(void);
void	prt_meows(void);

//builtin
void	builtin_echo(char **command);
void 	builtin_cd(char **command, t_envnode *envnode , int last_flag);
void    builtin_pwd(char **command);
void	builtin_env(t_envnode *envnode, char **command, int last_flag);
void	builtin_export(t_envnode *envnode, char **command, int last_flag);
void    builtin_unset(t_envnode *envnode, char **command);

void    create_heredoc_file(t_tree *tree);
void    delete_heredoc_file(t_tree *tree);
#endif
