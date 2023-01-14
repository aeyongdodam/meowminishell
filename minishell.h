/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:02:54 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/15 01:02:56 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
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
	struct s_node		*root;
	struct s_envnode	*env;
	int					pipe_cnt;
	int					ridi_cnt;
	int					heredoc_cnt;
	int					space;
	int					pipe;
	int					redi;
}	t_tree;

typedef struct s_pipe{
	pid_t	pid;
	int		**fd;
	int		heredoc_fd;
	int		openfd;
	int		finalfd;
	int		pipe_cnt;
	int		final;
	int		first;
	int		i;
	char	*file_name;
	int		index;
	int		err_code;
	char	*for_itoa;
	char	*str;
	char	**command;
	t_token	*tmp;
}	t_pipe;

typedef struct s_envnode
{
	struct s_envnode	*prev;
	struct s_envnode	*next;
	char				*key;
	char				*value;
}	t_envnode;

//signal.c
void		signal_handler(int sig);
void		signal_handler2(int sig);
void		set_signal_handler(int flag);
void		set_terminal(void);

//init.c
t_token		*init_token(void);
t_node		*init_node(void);
t_tree		*init_tree(void);
t_envnode	*init_env(char **envp, t_tree *tree, int i, int j);
t_envnode	*init_envnode(t_envnode	**head, char *str);

//lexer.c
int			get_type(char *line);
t_tree		*lexer(char	*line, t_envnode *envnode);

//lexer_token.c
void		save_token(t_node *node, char *str, int flag);
void		word_token(t_node *node, char **str, t_tree *tree);
t_node		*pipe_token(t_node *node, char **str, t_tree *tree);
void		redi_token(t_node *node, char **line, char **str, t_tree *tree);
void		check_quote(t_node *node, char **line, char **str, t_tree *tree);

//lexer_env.c
char		*change_env(char *str2, t_envnode *envnode);
int			check_dallor(t_node *node, char **line, char **str, t_tree *tree);

//lexer_utils.c
void		set_variable(t_tree *tree, int space, int pipe, int redi);
void		set_lexer(t_node **node, t_tree **tree, char **str, t_envnode *env);
void		set_quote(int *cash, int *flag, char **s, char **line);
void		double_redi(t_node *node, char **line, char **str, t_tree *tree);
void		save_quote(t_node *node, char **str, t_tree *tree, int flag);

//lexer_utils2.c
char		*str_one_join(char *s1, char c, t_tree *tree, int flag);
char		*re_str(char *str);
char		*re_str_join(char **str, char **s);
void		empty_line(char **line);
void		empty_quote(t_node *node, char **str, char **s, int cash);

//free.c
void		free_token(t_token **token);
void		free_node(t_node **node);
void		all_free(t_tree **tree, char *line);

//error.c
int			error_flag(t_node *node, t_token *token);
int			check_tree(t_node *node);
int			find_error(t_tree *tree, char *line);

//error_utils.c
void		prt_error(int flag, char *str);
int			check_pipe(t_node *node, int flag);
int			error_pipe(t_node *node);
int			error_redi(t_token *token);
int			error_quote(t_token *token);

//pipe.c
void		main_pipe(t_tree *tree, t_envnode *envnode, char **envp);
int			pipe_malloc_open_init(t_pipe *pi, int pipe_cnt, t_tree *tree);
void		wait_process(int cnt);
void		close_fd(t_pipe *pi, int cnt);
void		set_start(t_tree *tree, t_pipe *pi, t_envnode *envnode, t_node *tr);

//utils
void		prt_meows(void);
void		set_init_env(t_envnode **head, char **str);
void		set_oldpwd(t_envnode **head);
void		prt_exit(void);

//cd.c
char		*find_home(t_envnode *envnode);
char		*find_oldpwd(t_envnode *envnode);
void		update_oldpwd(t_envnode *envnode, char *s);
int			find_cd_path(char *s, char *buf, t_envnode *envnode, int last_flag);
int			builtin_cd(char **command, t_envnode *envnode, int last_flag);

//cd_utils.c
void		prt_cd_error(t_envnode *envnode, int flag);
int			cd_one_cmd(t_envnode *envnode, int last_flag, char *buf);
int			cd_cmd2(char **command, t_envnode *env, int last_flag, char *buf);
int			cd_home(char **command, t_envnode *env, int last_flag, char *buf);
int			cd_oldpwd(t_envnode *envnode, int last_flag, char *buf);

//echo.c
int			ft_newlinecmp(char *s);
void		builtin_echo(char **command);

//env.c
int			builtin_env(t_envnode *envnode, char **command, int last_flag);

//exit.c
int			num_check(char *s);
int			exit_utils(char **command, int last_flag);
int			builtin_exit(char **command, int last_flag);

//pwd.c
void		builtin_pwd(char **command);

//unset.c
void		unset_free(t_envnode **tmp, t_envnode **free_tmp);
int			builtin_unset(t_envnode *envnode, char **command);

//export.c
int			builtin_export(t_envnode *envnode, char **command, int last_flag);

//export_utils.c
void		prt_env(t_envnode *envnode);
int			find_key(char *key_tmp, char *value_tmp, t_envnode *envnode);
int			check_export_err(char *s);
t_envnode	*init_temp_env(t_envnode *envnode, t_envnode *start);
void		sort_env(t_envnode **envnode);

//export_utils2.c
void		free_export(t_envnode **node);
void		prt_export(t_envnode *envnode, int last_flag);
t_envnode	*init_new_export(void);
void		export_find(t_envnode **no, t_envnode **tmp, char **key, char **v);
void		export_new(t_envnode **node, t_envnode **tmp, char **key, char **v);

//child_and_parent_utils.c
void		handle_child(t_pipe *pi, char **envp, t_envnode *envnode);
void		child_process(t_node *tr, t_pipe *pi, char **envp, t_envnode *env);
void		parent_process(t_node *tr, t_pipe *pi);

//close_all_pipe.c
void		close_four_pipe(int a, int b, int c, int d);
void		close_three_pipe(int a, int b, int c);
void		close_two_pipe(int a, int b);
void		close_pipe(t_pipe *pi, int pipe_cnt);

//find_path.c
void		find_env_path(t_envnode *tmp, char **save_path);
char		*split_path(char *save_path, char *s);
char		*find_path(t_envnode *envnode, char *s);

//free_funcion.c
void		free_pipe(t_pipe *pi, int cnt);
void		free_split(char **split_path);

//get_command.c
char		**get_redi_command(t_node *tr);
char		**get_command(t_node *tr);

//handle_error.c
void		pipe_prt_error(int error_code, char *s);
void		check_stat(char *s);

//pipe_builtin_utils.c
void		builtin1(t_pipe *pi, t_envnode *envnode);
void		builtin2(t_pipe *pi, t_envnode *envnode);
int			builtin_strncmp(t_pipe *pi, t_tree *tree, t_node *tr);
void		handle_builtin_parent(t_tree *tree, t_node *tr, \
t_envnode *envnode, t_pipe *pi);

//pipe_connect.c
void		pipe_connect1(t_node *tr, t_pipe *pi, int i);
void		pipe_connect2(t_node *tr, t_pipe *pi, int i);
void		pipe_connect3(t_node *tr, t_pipe *pi, int i);
void		pipe_connect4(t_node *tr, t_pipe *pi, int i);
void		pipe_connect_other(t_node *tr, t_pipe *pi, int i);

//pipe_connect_fd.c
void		pipe_connect_openfd(t_pipe *pi);
void		pipe_connect_heredoc(t_pipe *pi);

//redi_command_utils.c
int			check_redi(t_node *tr);
int			redi_command_count(t_token *tmp);
char		**save_redi_command(t_token *tmp, int i);

//heredoc 개수 세주는거
int			heredoc_count(int index, t_token *t);
//builtin
void		create_heredoc_file(t_tree *tree);
void		delete_heredoc_file(t_tree *tree);

#endif
