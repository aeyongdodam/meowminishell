/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:09:58 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:47:03 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child(t_pipe *pi, char **envp, t_envnode *envnode)
{
	builtin1(pi, envnode);
	builtin2(pi, envnode);
	if (pi->str == NULL && (ft_strncmp(pi->command[0], "/", 1) == 0 \
	|| ft_strncmp(pi->command[0], "./", 2) == 0))
		pi->str = pi->command[0];
	execve(pi->str, pi->command, envp);
	write(2, "meowshell: ", 12);
	write(2, pi->command[0], ft_strlen(pi->command[0]));
	write(2, ": command not found\n", 21);
	exit (127);
}

void	child_process(t_node *tr, t_pipe *pi, char **envp, t_envnode *envnode)
{
	if (check_redi(tr) == 1)
	{
		pi->tmp = tr->left_child->token;
		while (pi->tmp)
		{
			if (ft_strncmp(pi->tmp->str, "<", 2) == 0 && pi->tmp->flag != 1)
				pipe_connect1(pi, pi->i);
			else if (!(ft_strncmp(pi->tmp->str, ">>", 3)) && pi->tmp->flag != 1)
				pipe_connect2(pi, pi->i);
			else if (!(ft_strncmp(pi->tmp->str, ">", 2)) && pi->tmp->flag != 1)
				pipe_connect3(pi, pi->i);
			else if (!(ft_strncmp(pi->tmp->str, "<<", 3)) && pi->tmp->flag != 1)
				pipe_connect4(pi, pi->i);
			pi->tmp = pi->tmp->next;
		}
	}
	else
		pipe_connect_other(pi, pi->i);
	close_fd(pi, pi->pipe_cnt);
	if (pi->err_code < 0)
		pipe_prt_error(4, "");
	handle_child(pi, envp, envnode);
}

void	parent_process(t_node *tr, t_pipe *pi)
{
	set_signal_handler(3);
	if (pi->i != 0)
	{
		close(pi->fd[(pi->i) - 1][0]);
		close(pi->fd[(pi->i) - 1][1]);
	}
	pi->index = heredoc_count(pi->index, tr->left_child->token);
	pi->i++;
	free_split(pi->command);
	free (pi->str);
}
