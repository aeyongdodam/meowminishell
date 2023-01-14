/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_connet_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:11:02 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:11:07 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_connect_openfd(t_pipe *pi)
{
	pi->openfd = open(pi->tmp->next->str, O_RDONLY);
	check_stat(pi->tmp->next->str);
	if (pi->openfd >= 0)
	{
		pi->err_code *= dup2(pi->openfd, 0);
		close(pi->openfd);
	}
	else
		pipe_prt_error(1, pi->tmp->next->str);
}

void	pipe_connect_heredoc(t_pipe *pi)
{
	pi->for_itoa = ft_itoa(pi->index);
	pi->file_name = ft_strjoin("tmp_file", pi->for_itoa);
	free(pi->for_itoa);
	pi->heredoc_fd = open(pi->file_name, O_RDONLY);
	free(pi->file_name);
	if (pi->heredoc_fd >= 0)
	{					
		pi->err_code *= dup2(pi->heredoc_fd, 0);
		close(pi->heredoc_fd);
	}
	else
		pipe_prt_error(1, pi->tmp->next->str);
}
