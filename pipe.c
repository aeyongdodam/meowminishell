#include "pipe.h"
#include "tree.h"
void	pipe_count(t_tree *tr, t_pipe *pi)
{
	pi->pipe_cnt = 1;
	while (tr->right_child)
	{
		pi->pipe_cnt++;
		tr=tr->right_child;
	}
}

void pipe_malloc_open(t_pipe *pi)
{
	int	i;

	i = 0;
	pi->fd = malloc(sizeof(pi.pipe_cnt * 2));
	while (i < pi.pipe_cnt * 2)
		pipe(fd[i++]);
}

void find_path(char **envp)
{
	int	i;
	char *save_path;
	i = 0;
	while (envp[i] ! = 0)
	{
		if (ft_strncmp("PATH=", envp[i], 5)
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
	split_path = ft_split(save_path, ":");
	

}

int main(char *envp[])
{
	t_pipe *pi;
	t_tree *tr;
	t_tree *tmp;
	t_tree *tmp2;
//트리 짜본거
	tr = malloc(sizeof(t_tree));
	pi = malloc(sizeof(t_pipe));
	tr->token = malloc(sizeof(t_token));
	tr->token->flag = 0;
	tmp = malloc(sizeof(t_pipe));
	tmp->token = malloc(sizeof(t_token));
	tr->right_child = tmp;
	tmp->token->flag = 1;
	tmp2 = malloc(sizeof(t_pipe));
	tmp2->token=malloc(sizeof(t_token));
	tmp->right_child = tmp2;
	tmp2->token->flag = 2;
//트리끝
	pipe_count(tr, pi);
	pipe_malloc_open(pi);


	int	i;
	pid_t	pid;
	char *str;

	i = 0;
	while (i < pi.pipe_cnt * 2)
	{
		dup2(fd[i], 0);
		dup2(fd[i + 1], 1);
		pid = fork();

		str = find_path(envp);
		if (pid == 0)
		{
			
		}



		i += 2;
	}

}