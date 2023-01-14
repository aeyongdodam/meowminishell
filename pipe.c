/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:54:06 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:09:29 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	pipe_malloc_open_init(t_pipe *pi, int pipe_cnt, t_tree *tree)
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
	pi->final = dup(1);
	pi->first = dup(0);
	pi->index = 0;
	pi->i = 0;
	pi->pipe_cnt = tree->pipe_cnt;
	return (0);
}

void	wait_process(void)
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
			if (signo == 13)
			{
				g_exit_code = WEXITSTATUS(status);
				continue ;
			}
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

void	close_fd(t_pipe *pi, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		close(pi->fd[i][0]);
		close(pi->fd[i][1]);
		i++;
	}
}

void	set_start(t_pipe *pi, t_envnode *envnode, t_node *tr)
{
	pi->err_code = 1;
	if (check_redi(tr) == 1)
		pi->command = get_redi_command(tr);
	else
		pi->command = get_command(tr);
	pi->str = find_path(envnode, pi->command[0]);
}

void	main_pipe(t_tree *tree, t_envnode *envnode, char **envp)
{
	t_pipe	*pi;
	t_node	*tr;

	tr = tree->root;
	pi = malloc(sizeof(t_pipe));
	if (pipe_malloc_open_init(pi, tree->pipe_cnt, tree) == -1)
		pipe_prt_error(2, "");
	if (!tr->left_child)
		return ;
	while (pi->i < tree->pipe_cnt + 1)
	{
		set_start(pi, envnode, tr);
		set_signal_handler(1);
		pi->pid = fork();
		if (pi->pid < 0)
			pipe_prt_error(3, "");
		if (pi->pid == 0)
			child_process(tr, pi, envp, envnode);
		parent_process(tr, pi);
		tr = tr->right_child;
	}
	wait_process();
	handle_builtin_parent(tree, tr, envnode, pi);
	free_pipe(pi, tree->pipe_cnt);
	free(pi);
}
