/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:14:43 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:19:39 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(int index, t_token *t)
{
	while (t)
	{
		if (ft_strncmp(t->str, "<<", 3) == 0 && t->flag == 6)
			index++;
		t = t->next;
	}
	return (index);
}

void	heredoc_line(t_heredoc *h, t_token *tmp)
{
	while (ft_strncmp(h->line, tmp->next->str, \
	ft_strlen(tmp->next->str) + 1) != 0)
	{
		h->for_free = h->save_line;
		h->save_line = ft_strjoin(h->save_line, h->line);
		free(h->line);
		free(h->for_free);
		h->for_free = h->save_line;
		h->save_line = ft_strjoin(h->save_line, "\n");
		free(h->for_free);
		h->line = readline("> ");
	}
	free(h->line);
}

void	heredoc_utils(t_heredoc *h)
{
	h->for_free = h->save_line;
	h->save_line = ft_strjoin(h->save_line, "\n");
	free(h->for_free);
	h->itoa_index = ft_itoa(h->index);
	h->file_name = ft_strjoin("tmp_file", h->itoa_index);
	free (h->itoa_index);
	h->heredoc_fd = open(h->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(h->file_name);
	write(h->heredoc_fd, h->save_line, ft_strlen(h->save_line) - 1);
	free(h->save_line);
	h->index++;
}

void	handle_heredoc_flag(t_heredoc *h, t_token *tmp)
{
    h->save_line = ft_calloc(1, 1);
	set_signal_handler (0);
	h->line = readline("> ");
	if (h->line)
		heredoc_line(h, tmp);
	heredoc_utils(h);
}
