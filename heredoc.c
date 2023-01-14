/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:35:01 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:19:47 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_heredoc_file(t_tree *tree)
{
	int		index;
	char	*file_name;
	char	*itoa_index;

	index = 0;
	while (index < tree->heredoc_cnt)
	{
		itoa_index = ft_itoa(index);
		file_name = ft_strjoin("tmp_file", itoa_index);
		free (itoa_index);
		unlink (file_name);
		free(file_name);
		index++;
	}
}

void	create_heredoc_file(t_tree *tree)
{
	t_node		*tr;
	t_token		*tmp;
	t_heredoc	*h;
	int			i;

	h = malloc(sizeof(t_heredoc));
	tr = tree->root;
	i = 0;
	h->index = 0;
	while (i < tree->pipe_cnt + 1)
	{
		tmp = tr->left_child->token;
		while (tmp)
		{
			if (ft_strncmp(tmp->str, "<<", 3) == 0 && tmp->flag == 6)
				handle_heredoc_flag(h, tmp);
			tmp = tmp->next;
		}
		tr = tr->right_child;
		i++;
	}
	free(h);
	tree->heredoc_cnt = h->index;
}
