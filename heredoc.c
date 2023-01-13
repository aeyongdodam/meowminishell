
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
    while (index < tree->heredoc_cnt)
    {
        file_name = ft_strjoin("tmp_file", ft_itoa(index));        
        unlink(file_name);
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
    i = 0;
    index = 0;
    int heredoc_fd;
    save_line = ft_calloc(1,1);
    while (i < tree->pipe_cnt + 1)
    {
        tmp = tr->left_child->token;
        while (tmp)
        {
            if (ft_strncmp(tmp->str, "<<", 3) == 0 && tmp->flag == 6)
            {
                save_line = ft_calloc(1,1);
 		        line = readline("\033[34m>\033[0m ");
                while (ft_strncmp(line, tmp->next->str, ft_strlen(tmp->next->str) + 1) != 0)
                {
                    save_line = ft_strjoin(save_line, line);
                    save_line = ft_strjoin(save_line, "\n");
                    line = readline("\033[34m>\033[0m ");
                }
                save_line = ft_strjoin(save_line, "\n");
                file_name = ft_strjoin("tmp_file", ft_itoa(index));
                heredoc_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                write(heredoc_fd, save_line, ft_strlen(save_line) - 1);
                index++;
            }
            tmp = tmp->next;
        }
        tr = tr->right_child;
        i++;
    }
    tree->heredoc_cnt = index;
}