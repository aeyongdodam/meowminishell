
#include "minishell.h"


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
            if (ft_strncmp(tmp->str, "<<", 3) == 0)
            {
 		        line = readline("\033[34m>\033[0m ");
                while (ft_strncmp(line, tmp->next->str, ft_strlen(tmp->next->str) + 1) != 0)
                {
                    save_line = ft_strjoin(save_line, line);
                    save_line = ft_strjoin(save_line, "\n");
                    line = readline("\033[34m>\033[0m ");
                }
                file_name = ft_strjoin("tmp_file", ft_itoa(index));
                heredoc_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                // printf("heredoc_fd %d\n",heredoc_fd);
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