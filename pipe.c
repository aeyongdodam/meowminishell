
#include "minishell.h"

void	pipe_count(t_node *tr, t_pipe *pi)
{
	pi->pipe_cnt = 0;
//	printf("lll tr-> %s\n",tr->left_child->token->str);
	while (tr->right_child)
	{
		pi->pipe_cnt++;
		tr=tr->right_child;
	}

}

void pipe_malloc_open(t_pipe *pi,int pipe_cnt)
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

char	*find_path(char **envp, char *s)
{
	int	i;
	char *save_path;
	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			save_path = ft_strdup(envp[i]);
			break;
		}
		i++;
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

void	main_pipe(t_tree *tree, char *envp[])
{
	t_pipe *pi;
	t_node *tr;

	tr = tree->root;
	int j = 0;
	pipe_malloc_open(pi, tree->pipe_cnt);
	int	i;
	pid_t	pid;
	char *str;
	int openfd;
	char **command;
	int final = dup(1);

	if (!tr->left_child)
		return ;
	i = 0;
	while (i < tree->pipe_cnt + 1)
	{
	//path 구하기 시작

		str = find_path(envp, tr->left_child->token->str);
		command = get_command(tr);
	//path 구함
		pid = fork();
		if (pid == 0) //자식 프로세스
		{

			if (i == tree->pipe_cnt)
			{
				if (i != 0)
				{
					dup2(pi->fd[i-1][0], 0);
					dup2(final, 1);
					close(pi->fd[i - 1][0]);
					close(pi->fd[i - 1][1]);
					close(final);
				}
			}
			else if (i == 0)
			{
				openfd = open(NULL, O_RDONLY, 0644);
				dup2(openfd, 0);
				dup2(pi->fd[i][1], 1);
				close(pi->fd[i][0]);
				close(openfd);
				close(pi->fd[i][1]);
			}
			else
			{
				dup2(pi->fd[i-1][0], 0);
				dup2(pi->fd[i][1], 1);
				close(pi->fd[i-1][0]);
				close(pi->fd[i-1][1]);
				close(pi->fd[i][0]);
				close(pi->fd[i][1]);
			}
			execve(str, command, envp);
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
}