#include "pipe.h"
#include "tree.h"
#include "libft/libft.h"
#include <fcntl.h>
void	pipe_count(t_node *tr, t_pipe *pi)
{
	pi->pipe_cnt = 0;
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
	pi->fd = malloc(sizeof(int *) * pi->pipe_cnt);
	while (i < pi->pipe_cnt)
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

	i = 0;
	while (i++ < cnt)
		wait(NULL);
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
		//printf("save_command[i] %s\n",save_command[i]);
		tmp = tmp->next;
		i++;
	}
	save_command[i] = 0;
	return (save_command);
}

int main(int argc, char **argv, char *envp[])
{
	t_pipe *pi;
	t_node *tr;
	t_node *tmp;
	t_node *tmp2;


	int j = 0;
//트리 짜본거
	tr = malloc(sizeof(t_node));
	pi = malloc(sizeof(t_pipe));
	tr->token = malloc(sizeof(t_token));
	tr->token->str = "start";

	tr->left_child = malloc(sizeof(t_node));
	tr->left_child->token = malloc(sizeof(t_token));
	tr->left_child->token->str = "grep";
	tr->left_child->token->next = malloc(sizeof(t_token));
	tr->left_child->token->next->str = "a";
	tr->left_child->token->next->next = malloc(sizeof(t_token));
	tr->left_child->token->next->next->str = "Makefile";
	tr->left_child->token->next->next->next = malloc(sizeof(t_token));
	tr->left_child->token->next->next->next->str = "a.txt";

	tmp = malloc(sizeof(t_node));
	tmp->token = malloc(sizeof(t_token));
	tr->right_child = tmp;

	tmp->left_child = malloc(sizeof(t_node));
	tmp->left_child->token = malloc(sizeof(t_token));
	tmp->left_child->token->str = "ls";
	tmp->left_child->token->next = malloc(sizeof(t_token));
	tmp->left_child->token->next->str = "-la";

	tmp2 = malloc(sizeof(t_pipe));
	tmp2->token=malloc(sizeof(t_token));
	tmp->right_child = tmp2;

	tmp2->left_child = malloc(sizeof(t_node));
	tmp2->left_child->token = malloc(sizeof(t_token));
	tmp2->left_child->token->str = "wc";
	tmp2->left_child->token->next = malloc(sizeof(t_token));
	tmp2->left_child->token->next->str = "-l";

//트리끝


	pipe_count(tr, pi);
	pipe_malloc_open(pi);
	int	i;
	pid_t	pid;
	char *str;
	int openfd;
	char **command;
	int final = dup(1);

	i = 0;
	while (i < pi->pipe_cnt + 1)
	{
	//path 구하기 시작
		str = find_path(envp, tr->left_child->token->str);
		command = get_command(tr);
	//path 구함

		pid = fork();
		if (pid == 0) //자식 프로세스
		{
			if (i == 0)
			{
				openfd = open(NULL, O_RDONLY, 0644);
				dup2(openfd, 0);
				dup2(pi->fd[i][1], 1);
				close(pi->fd[i][0]);
				close(openfd);
				close(pi->fd[i][1]);
			}
			else if (i == pi->pipe_cnt)
			{
				dup2(pi->fd[i-1][0], 0);
				dup2(final, 1);
				close(pi->fd[i - 1][0]);
				close(pi->fd[i - 1][1]);
				close(final);
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
	wait_process(pi->pipe_cnt); //다 끝날때까지 부모 프로세스 기다려야함
}