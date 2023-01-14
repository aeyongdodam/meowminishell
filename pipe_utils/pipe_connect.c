/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_connect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:56 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:10:59 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_connect1(t_pipe *pi, int i)
{
	pipe_connect_openfd(pi);
	if (i == pi->pipe_cnt)
	{
		if (i != 0)
		{
			pi->err_code *= dup2(pi->final, 1);
			close_three_pipe(pi->final, pi->fd[i - 1][0], pi->fd[i - 1][1]);
		}
	}
	else if (i == 0)
	{
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close_two_pipe(pi->fd[i][0], pi->fd[i][1]);
	}
	else
	{
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close_four_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1], \
		pi->fd[i][0], pi->fd[i][1]);
	}
}

void	pipe_connect2(t_pipe *pi, int i)
{
	pi->finalfd = open(pi->tmp->next->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	check_stat(pi->tmp->next->str);
	if (pi->finalfd >= 0)
	{
		pi->err_code *= dup2(pi->finalfd, 1);
		close(pi->finalfd);
	}
	else
		pipe_prt_error(1, pi->tmp->next->str);
	if (i == pi->pipe_cnt)
	{
		if (i != 0)
		{
			pi->err_code *= dup2(pi->fd[i - 1][0], 0);
			close_two_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1]);
		}
	}
	else if (i == 0)
		close_two_pipe(pi->fd[i][0], pi->fd[i][1]);
	else
	{
		pi->err_code *= dup2(pi->fd[i - 1][0], 0);
		close_four_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1], \
		pi->fd[i][0], pi->fd[i][1]);
	}
}

void	pipe_connect3(t_pipe *pi, int i)
{
	pi->finalfd = open(pi->tmp->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_stat(pi->tmp->next->str);
	if (pi->finalfd >= 0)
	{
		pi->err_code *= dup2(pi->finalfd, 1);
		close(pi->finalfd);
	}
	else
		pipe_prt_error(1, pi->tmp->next->str);
	if (i == pi->pipe_cnt)
	{
		if (i != 0)
		{
			pi->err_code *= dup2(pi->fd[i - 1][0], 0);
			close_two_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1]);
		}
	}
	else if (i == 0)
		close_two_pipe(pi->fd[i][0], pi->fd[i][1]);
	else
	{
		pi->err_code *= dup2(pi->fd[i - 1][0], 0);
		close_four_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1], \
		pi->fd[i][0], pi->fd[i][1]);
	}
}

void	pipe_connect4(t_pipe *pi, int i)
{
	pipe_connect_heredoc(pi);
	pi->index++;
	if (i == pi->pipe_cnt)
	{
		if (i != 0)
		{
			pi->err_code *= dup2(pi->final, 1);
			close_two_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1]);
		}
	}
	else if (i == 0)
	{
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close_two_pipe(pi->fd[i][0], pi->fd[i][1]);
	}
	else
	{
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close_four_pipe(pi->fd[i - 1][0], pi->fd[i - 1][1], \
		pi->fd[i][0], pi->fd[i][1]);
	}
}

void	pipe_connect_other(t_pipe *pi, int i)
{
	if (i == pi->pipe_cnt)
	{
		if (i != 0)
		{
			pi->err_code *= dup2(pi->fd[i - 1][0], 0);
			pi->err_code *= dup2(pi->final, 1);
			close(pi->fd[i - 1][0]);
			close(pi->fd[i - 1][1]);
		}
	}
	else if (i == 0)
	{
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close(pi->fd[i][0]);
		close(pi->fd[i][1]);
	}
	else
	{
		pi->err_code *= dup2(pi->fd[i - 1][0], 0);
		pi->err_code *= dup2(pi->fd[i][1], 1);
		close(pi->fd[i - 1][0]);
		close(pi->fd[i - 1][1]);
		close(pi->fd[i][0]);
		close(pi->fd[i][1]);
	}
}
