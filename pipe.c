
#include "minishell.h"

void pipe_malloc_open(t_pipe *pi, int pipe_cnt)
{
	int	i;

	i = 0;
	pi->fd = malloc(sizeof(int *) * pipe_cnt);
	while (i < pipe_cnt)
	{
		pi->fd[i] = malloc(sizeof(int) * 2);
		pipe(pi->fd[i]);
		i++;
	}
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

char	*find_path(t_envnode *envnode, char *s)
{
	t_envnode *tmp;
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
	if (!save_path)
		return (NULL);
	save_path = ft_substr(save_path, 5, ft_strlen(save_path));
	char **split_path;
	split_path = ft_split(save_path, ':');
	i = 0;
	while(split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		split_path[i] = ft_strjoin(split_path[i], s);
		if (access(split_path[i], X_OK) == 0)
			return (split_path[i]);
		i++;
	}
	return (NULL);
}

void wait_process(int cnt)
{
	int	i;
	int	status;

	i = 0;
	while (i < cnt + 1)
	{
		wait(NULL);
		i++;
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
		if (ft_strncmp(tmp->str, "<", 2) == 0 || ft_strncmp(tmp->str, ">>", 3) == 0 || ft_strncmp(tmp->str, ">", 2) == 0)
			i -= 2; //일단은 유효한것만 들어온다고 생각
		i++;
		tmp = tmp->next;
	}
	tmp = tr->left_child->token;
	save_command = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		if (ft_strncmp(tmp->str, "<", 2) == 0 || ft_strncmp(tmp->str, ">>", 3) == 0 || ft_strncmp(tmp->str, ">", 2) == 0)
			tmp = tmp->next->next;
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

int	check_redi(t_node *tr)
{
	int	flag;

	flag = 0;
	t_token *tmp;

	tmp = tr->left_child->token;
	while(tmp)
	{
	if (ft_strncmp(tmp->str, ">", 2) == 0 || ft_strncmp(tmp->str, "<", 2) == 0 || \
	ft_strncmp(tmp->str, ">>", 3) == 0)
		flag = 1;
	tmp = tmp->next;
	}
	return (flag);
}



void	main_pipe(t_tree *tree, t_envnode *envnode, char **envp)
{
	t_pipe *pi;
	t_node *tr;

	tr = tree->root;
	pi = malloc(sizeof(t_pipe));
	int j = 0;
	pipe_malloc_open(pi, tree->pipe_cnt);
	int	i;
	pid_t	pid;
	char *str;
	int openfd;
	int finalfd;
	char **command;
	int redi_flag;
	t_token	*tmp;
	pi->cd_cnt = 0;
	int final = dup(1);

	if (!tr->left_child)
		return ;
	i = 0;
	while (i < tree->pipe_cnt + 1)
	{
	//path 구하기 시작

		str = find_path(envnode, tr->left_child->token->str);
		if (check_redi(tr) == 1)
			command = get_redi_command(tr);
		else
			command = get_command(tr);
	//path 구함
	pid = fork();
	if (pid == 0)
	{
		if (check_redi(tr) == 1)
		{
			tmp = tr->left_child->token;
			while (tmp)
			{
				if (ft_strncmp(tmp->str, "<", 2) == 0)
					{
						openfd =  open(tmp->next->str, O_RDONLY);
						if (openfd >= 0)
							dup2(openfd, 0);
					}
				if (ft_strncmp(tmp->str, ">>", 3) == 0)
				{
					finalfd = open(tmp->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
					if (finalfd >= 0)
						dup2(finalfd, 1);
				}
				else if (ft_strncmp(tmp->str, ">", 2) == 0)
				{
					finalfd = open(tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
					if (finalfd >= 0)
						dup2(finalfd, 1);
				}
				tmp = tmp->next;

			}
		}
		else if (i == tree->pipe_cnt)
		{
			if (i != 0)
			{
				dup2(pi->fd[i - 1][0], 0);
				dup2(final, 1);
				close(pi->fd[i - 1][0]);
				close(pi->fd[i - 1][1]);
			}
		}
		else if (i == 0)
		{
			dup2(pi->fd[i][1], 1);
			close(pi->fd[i][0]);
			close(pi->fd[i][1]);
		}
		else
		{
			dup2(pi->fd[i - 1][0], 0);
			dup2(pi->fd[i][1], 1);
			close(pi->fd[i - 1][0]);
			close(pi->fd[i - 1][1]);
			close(pi->fd[i][0]);
			close(pi->fd[i][1]);
		}

		if (ft_strncmp(command[0], "echo", 5) == 0)
		{
			builtin_echo(command);
			exit (0);
		}
		else if(ft_strncmp(command[0], "cd", 3) == 0)
		{
			pi->cd_cnt += 1;
			builtin_cd(command, envnode);
			exit (0);
		}
		else if(ft_strncmp(command[0], "pwd", 4) == 0)
		{
			builtin_pwd(command);
			exit (0);
		}
		else if(ft_strncmp(command[0], "env", 4) == 0)
		{
			builtin_env(envnode);
			exit (0);
		}
		else if(ft_strncmp(command[0], "export", 7) == 0)
		{
			builtin_export(envnode, command);
			exit (0);
		}
		else
		{
			if (str == NULL && (ft_strncmp(command[0], "/", 1) == 0 || ft_strncmp(command[0], "./", 2) == 0))
				str = command[0];
			execve(str, command, envp);
			write(2, "error\n", 6);
			exit (1);
		}
	}
	if (i != 0)
	{
		close(pi->fd[i-1][0]);
		close(pi->fd[i-1][1]);
	}
		tr=tr->right_child;
		 i++;
	}
	wait_process(tree->pipe_cnt); //다 끝날때까지 부모 프로세스 기다려야함
	tr = tree->root;
	if (tree->pipe_cnt == 0 && ft_strncmp(tr->left_child->token->str, "cd", 3) == 0)
	{
		str = find_path(envnode, tr->left_child->token->str);
		command = get_command(tr);
		builtin_cd(command, envnode);
	}
}