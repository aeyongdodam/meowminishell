/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:35:01 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 23:42:57 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int heredoc_count(int index, t_token *t)
{
    while(t)
    {
        if (ft_strncmp(t->str, "<<", 3) == 0 && t->flag == 6)
            index++;
        t = t->next;
    }
    return (index);
}

void    delete_heredoc_file(t_tree *tree)
{
    int index;
    index = 0;
    char *file_name;
    char    *itoa_index;
    while (index < tree->heredoc_cnt)
    {
        itoa_index = ft_itoa(index);
        file_name = ft_strjoin("tmp_file", itoa_index);
        free (itoa_index);
        unlink(file_name);
        free(file_name);
        index++;
    }
}

void    create_heredoc_file(t_tree *tree)
{
    t_node *tr;
    tr = tree->root;
    t_token *tmp;

    int i;
    int index;
    char *file_name;
    char *line;
    char *save_line;
    char    *itoa_index;
    char    *for_free;
    i = 0;
    index = 0;
    int heredoc_fd;
    while (i < tree->pipe_cnt + 1)
    {
        tmp = tr->left_child->token;
        while (tmp)
        {
            if (ft_strncmp(tmp->str, "<<", 3) == 0 && tmp->flag == 6)
            {
                save_line = ft_calloc(1,1);
                set_signal_handler(0);
 		        line = readline("> ");
                if (line)
                {
                    while (ft_strncmp(line, tmp->next->str, ft_strlen(tmp->next->str) + 1) != 0)
                    {
                        for_free = save_line;
                        save_line = ft_strjoin(save_line, line);
                        free(line);
                        free(for_free);
                        for_free = save_line;
                        save_line = ft_strjoin(save_line, "\n");
                        free(for_free);
                        line = readline("> ");
                    }
                    free(line);
                }
                for_free = save_line;
                save_line = ft_strjoin(save_line, "\n");
                free(for_free);
                itoa_index = ft_itoa(index);
                file_name = ft_strjoin("tmp_file", itoa_index);
                free (itoa_index);
                heredoc_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                free(file_name);
                write(heredoc_fd, save_line, ft_strlen(save_line) - 1);
                free(save_line);
                index++;
            }
            tmp = tmp->next;
        }
        tr = tr->right_child;
        i++;
    }
    tree->heredoc_cnt = index;
}