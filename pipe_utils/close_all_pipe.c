/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:08 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:10:15 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_four_pipe(int a, int b, int c, int d)
{
	close(a);
	close(b);
	close(c);
	close(d);
}

void	close_three_pipe(int a, int b, int c)
{
	close (a);
	close (b);
	close (c);
}

void	close_two_pipe(int a, int b)
{
	close (a);
	close (b);
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