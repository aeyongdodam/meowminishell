
#include "minishell.h"
extern int	g_exit_code;
int	pipe_malloc_open(t_pipe *pi, int pipe_cnt)
{
	int	i;
	int	err_code;
	i = 0;
	pi->fd = malloc(sizeof(int *) * pipe_cnt);
	while (i < pipe_cnt)
	{
		pi->fd[i] = malloc(sizeof(int) * 2);
		err_code = pipe(pi->fd[i]);
		if (err_code == -1)
			return (err_code);
		i++;
	}
	return (0);
}

void	close_pipe(t_pipe *pi, int pipe_cnt)
{
	int	i;
	i = 0;
	while (i < pipe_cnt)
	{
		close(pi->fd[i][0]);
		close(pi->fd[i][1]);
		i++;
	}
}


void	free_split(char **split_path)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
}

char	*find_path(t_envnode *envnode, char *s)
{
	t_envnode	*tmp;
	char		*for_free;
	int	i;
	char *save_path;
	i = 0;
	tmp = envnode;
	while (tmp != 0)
	{
		if (ft_strncmp("PATH", tmp->key, 4) == 0)
		{
			save_path = ft_strdup(tmp->value);
			break;
		}
		tmp = tmp->next;
	}
	if (!save_path[0])
		return (NULL);
	for_free = save_path;
	save_path = ft_substr(save_path, 5, ft_strlen(save_path));
	// free(for_free);
	char **split_path;
	char	*ret;
	ret = NULL;
	split_path = ft_split(save_path, ':');
	free(save_path);
	i = 0;
	while(split_path[i])
	{
		for_free = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		free(for_free);
		for_free = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], s);
		free(for_free);
		if (access(split_path[i], X_OK) == 0)
			ret = ft_strdup(split_path[i]);
		i++;
	}
	free_split(split_path);
	return (ret);
}

void wait_process(int cnt)
{
	int		status;
	int		signo;
	int		i;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_code = 128 + signo;
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
}

char **get_redi_command(t_node *tr)
{
	t_token *tmp;
	int	i = 0;
	int	j = 0;
	tmp = tr->left_child->token;
	char **save_command;
	while (tmp)
	{
		if (tmp->flag != 1)
		{
			if (ft_strncmp(tmp->str, "<", 2) == 0 || ft_strncmp(tmp->str, ">>", 3) == 0 || ft_strncmp(tmp->str, ">", 2) == 0 || ft_strncmp(tmp->str, "<<", 3) == 0)
				i -= 2;
		}
		i++;
		tmp = tmp->next;
	}
	tmp = tr->left_child->token;
	save_command = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		if (tmp->flag != 1)
		{
		if (ft_strncmp(tmp->str, "<", 2) == 0 || ft_strncmp(tmp->str, ">>", 3) == 0 || ft_strncmp(tmp->str, ">", 2) == 0 || ft_strncmp(tmp->str, "<<", 3) == 0)
			tmp = tmp->next->next;
		}
		save_command[j] = tmp->str;

		tmp = tmp->next;
		j++;
	}
	save_command[j] = NULL;
	return (save_command);
}

char **get_command(t_node *tr)
{
	int	i;
	int	j;
	char **save_command;
	t_token *tmp;
	tmp = tr->left_child->token;

	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}//여기까지 세서 몇 개 command로 넘겨줄건지 결정
	save_command = malloc(sizeof(char *) * (i + 1));
	tmp = tr->left_child->token;
	i = 0;
	while (tmp)
	{
		save_command[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	save_command[i] = 0;
	return (save_command);
}


void	close_fd(t_pipe *pi, int cnt)
{
	int	i = 0;
	while (i < cnt)
	{
		close(pi->fd[i][0]);
		close(pi->fd[i][1]);
		i++;
	}
}

int	check_redi(t_node *tr)
{
	int	flag;

	flag = 0;
	t_token *tmp;

	tmp = tr->left_child->token;
	while(tmp)
	{
		if (tmp->flag != 1)
		{
			if (ft_strncmp(tmp->str, ">", 2) == 0 || ft_strncmp(tmp->str, "<", 2) == 0 || \
			ft_strncmp(tmp->str, ">>", 3) == 0 || ft_strncmp(tmp->str, "<<", 3) == 0)
			flag = 1;
		}
		tmp = tmp->next;
	}
	return (flag);
}



void	pipe_prt_error(int	error_code, char *s)
{
	if (error_code == 1)
	{
		write(2, "meowshell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 21);
		exit (1);
	}
	else if (error_code == 2)
	{
		write(2, "meowshell: pipe open error\n", 28);
		g_exit_code = 1;
	}
	else if (error_code == 3)
	{
		write(2, "meowshell: fork error\n", 23);
		g_exit_code = 1;
	}
	else if (error_code == 4)
	{
		write(2, "meowshell: dup error\n", 22);
		exit (1);
	}
}

void	free_pipe(t_pipe *pi, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		free(pi->fd[i]);
		i++;
	}
	free(pi->fd);
}

void	check_stat(char *s)
{
	struct stat buf;
	if (stat(s, &buf) == -1)
	{
		write(2, "meowshell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, " : No such file or directory\n", 30);
		exit(1);
	}

}


void	main_pipe(t_tree *tree, t_envnode *envnode, char **envp)
{
	t_pipe *pi;
	t_node *tr;

	tr = tree->root;
	pi = malloc(sizeof(t_pipe));
	if (pipe_malloc_open(pi, tree->pipe_cnt) == -1)
		pipe_prt_error(2, "");
	int j = 0;
	int heredoc_fd;
	int	err_code;

	int	i;
	char	*for_itoa;
	pid_t	pid;
	char *str;
	int openfd;
	int finalfd;
	char **command;
	t_token	*tmp;
	pi->cd_cnt = 0;
	int final = dup(1);
	int first = dup(0);
	int	index = 0;
	char *file_name;
	if (!tr->left_child)
		return ;
	i = 0;
	while (i < tree->pipe_cnt + 1)
	{
		err_code = 1;
		if (check_redi(tr) == 1)
			command = get_redi_command(tr);
		else
			command = get_command(tr); // command를 쪼개서 넣어주는거
	str = find_path(envnode, command[0]);
	set_signal_handler(1);
	pid = fork();
	if (pid < 0)
		pipe_prt_error(3, "");
	if (pid == 0)
	{
		if (check_redi(tr) == 1)
		{
			tmp = tr->left_child->token;
			while (tmp)
			{
				if (ft_strncmp(tmp->str, "<", 2) == 0 && tmp->flag != 1)
				{

					openfd =  open(tmp->next->str, O_RDONLY);
					check_stat(tmp->next->str);
					if (openfd >= 0)
					{
						err_code *= dup2(openfd, 0);
						close(openfd);
					}
					else
						pipe_prt_error(1, tmp->next->str);
					if (i == tree->pipe_cnt)
					{
						if (i != 0)
						{
							err_code *= dup2(final, 1);
							close(final);
							close(pi->fd[i - 1][0]);
							close(pi->fd[i - 1][1]);
						}
					}
					else if (i == 0)
					{
						err_code *= dup2(pi->fd[i][1], 1);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
					else
					{
						err_code *= dup2(pi->fd[i][1], 1);
						close(pi->fd[i - 1][0]);
						close(pi->fd[i - 1][1]);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}

				}

				else if (ft_strncmp(tmp->str, ">>", 3) == 0 && tmp->flag != 1)
				{

					finalfd = open(tmp->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
					check_stat(tmp->next->str);
					if (finalfd >= 0)
					{
						err_code *= dup2(finalfd, 1);
						close(finalfd);
					}
					else
						pipe_prt_error(1, tmp->next->str);
					if (i == tree->pipe_cnt)
					{
						if (i != 0)
						{
							err_code *= dup2(pi->fd[i - 1][0], 0);
							close(pi->fd[i - 1][0]);
							close(pi->fd[i - 1][1]);
						}
					}
					else if (i == 0)
					{
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
					else
					{
						err_code *= dup2(pi->fd[i - 1][0], 0);
						close(pi->fd[i - 1][0]);
						close(pi->fd[i - 1][1]);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
				}

				else if (ft_strncmp(tmp->str, ">", 2) == 0 && tmp->flag != 1)
				{
					finalfd = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
					check_stat(tmp->next->str);
					if (finalfd >= 0)
					{
						err_code *= dup2(finalfd, 1);
						close(finalfd);
					}
					else
						pipe_prt_error(1, tmp->next->str);
					if (i == tree->pipe_cnt)
					{
						if (i != 0)
						{
							err_code *= dup2(pi->fd[i - 1][0], 0);
							close(pi->fd[i - 1][0]);
							close(pi->fd[i - 1][1]);
						}
					}
					else if (i == 0)
					{
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
					else
					{
						err_code *= dup2(pi->fd[i - 1][0], 0);
						close(pi->fd[i - 1][0]);
						close(pi->fd[i - 1][1]);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
				}
				else if (ft_strncmp(tmp->str, "<<", 3) == 0 && tmp->flag != 1)
				{
					for_itoa = ft_itoa(index);
					file_name = ft_strjoin("tmp_file", for_itoa);
					free(for_itoa);
					heredoc_fd = open(file_name, O_RDONLY);
					free(file_name);
					if (heredoc_fd >= 0)
					{					
						err_code *= dup2(heredoc_fd, 0);
						close(heredoc_fd);
					}
					else
						pipe_prt_error(1, tmp->next->str);
					index++;
					if (i == tree->pipe_cnt)
					{
						if (i != 0)
						{
							err_code *= dup2(final, 1);
							close(pi->fd[i - 1][0]);
							close(pi->fd[i - 1][1]);
						}
					}
					else if (i == 0)
					{
						err_code *= dup2(pi->fd[i][1], 1);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
					else
					{
						err_code *= dup2(pi->fd[i][1], 1);
						close(pi->fd[i - 1][0]);
						close(pi->fd[i - 1][1]);
						close(pi->fd[i][0]);
						close(pi->fd[i][1]);
					}
				}
				tmp = tmp->next;
			}
		}
		else if (i == tree->pipe_cnt)
		{
			if (i != 0)
			{
				err_code *= dup2(pi->fd[i - 1][0], 0);
				err_code *= dup2(final, 1);
				close(pi->fd[i - 1][0]);
				close(pi->fd[i - 1][1]);
			}
		}
		else if (i == 0)
		{
			err_code *= dup2(pi->fd[i][1], 1);
			close(pi->fd[i][0]);
			close(pi->fd[i][1]);
		}
		else
		{
			err_code *= dup2(pi->fd[i - 1][0], 0);
			err_code *= dup2(pi->fd[i][1], 1);
			close(pi->fd[i - 1][0]);
			close(pi->fd[i - 1][1]);
			close(pi->fd[i][0]);
			close(pi->fd[i][1]);
		}
		close_fd(pi, tree->pipe_cnt);
		if (err_code < 0)
			pipe_prt_error(4, "");
//파이프연결 끝
		// printf("들어가기전 command 0 %s 1 %s\n",command[0],command[1]);
		if (!command[0] && index > 0)
			exit (0);
		else if (ft_strncmp(command[0], "echo", 5) == 0)
		{
			builtin_echo(command);
			exit (0);
		}
		else if(ft_strncmp(command[0], "cd", 3) == 0)
		{
			pi->cd_cnt += 1;
			exit (builtin_cd(command, envnode, 0));
		}
		else if(ft_strncmp(command[0], "pwd", 4) == 0)
		{
			builtin_pwd(command);
			exit (0);
		}
		else if(ft_strncmp(command[0], "env", 4) == 0)
		{
			exit(builtin_env(envnode, command, 0));
			exit (0);
		}
		else if(ft_strncmp(command[0], "export", 7) == 0)
			exit (builtin_export(envnode, command, 0));
		else if (ft_strncmp(command[0], "unset", 6) == 0)
		{
			builtin_unset(envnode, command);
			exit (0);
		}
		else if (ft_strncmp(command[0], "exit", 5) == 0)
			exit(builtin_exit(command, 0));
		else if (ft_strncmp(command[0], "$?", 3) == 0)
		{
			write(2, "meowshell: ", 12);
			write(2, ft_itoa(g_exit_code), ft_strlen(ft_itoa(g_exit_code)));
			write(2, ": command not found\n", 21);
			exit (127);			
		}
		else
		{
			if (str == NULL && (ft_strncmp(command[0], "/", 1) == 0 || ft_strncmp(command[0], "./", 2) == 0))
				str = command[0];
			execve(str, command, envp);
			write(2, "meowshell: ", 12);
			write(2, command[0], ft_strlen(command[0]));
			write(2, ": command not found\n", 21);
			exit (127);
		}
	}
		set_signal_handler(3);
		if (i != 0)
		{
			close(pi->fd[i-1][0]);
			close(pi->fd[i-1][1]);
		}
		index = heredoc_count(index, tr->left_child->token);
		tr=tr->right_child;
		i++;
	free_split(command);
	free(str);
	}

	wait_process(tree->pipe_cnt);
	tr = tree->root;
	if (tree->pipe_cnt == 0 && (ft_strncmp(tr->left_child->token->str, "cd", 3) == 0 || \
	ft_strncmp(tr->left_child->token->str, "export", 7) == 0) || (ft_strncmp(tr->left_child->token->str, "unset", 6) == 0 && !tr->right_child)\
	|| (ft_strncmp(tr->left_child->token->str, "exit", 5) == 0 && !tr->right_child))
	{
		str = find_path(envnode, tr->left_child->token->str);
		if (check_redi(tr))
			command = get_redi_command(tr);
		else
			command = get_command(tr);
		if (ft_strncmp(tr->left_child->token->str, "cd", 3) == 0)
			g_exit_code = builtin_cd(command, envnode, 1);
		else if (ft_strncmp(tr->left_child->token->str, "export", 7) == 0)
			g_exit_code = builtin_export(envnode, command, 1);
		else if (ft_strncmp(tr->left_child->token->str, "exit", 5) == 0)
			exit(builtin_exit(command, 1));
		else
			g_exit_code = builtin_unset(envnode, command);
		free_split(command);
		free(str);
	}
	free_pipe(pi, tree->pipe_cnt);
	free(pi);
}