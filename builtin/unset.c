
#include "../minishell.h"

void    builtin_unset(t_envnode *envnode, char **command)
{
	t_envnode *tmp;
	tmp = envnode;
	t_envnode *free_tmp;

	int     i;

	i = 1;
	if (!command[1])
		return ;
	while (command[i])
	{
		if (ft_strncmp(tmp->key, command[i], ft_strlen(command[i])) == 0) //첫번째 값일 때
		{

			free_tmp = tmp;
			envnode = envnode->next;
			free_tmp->key = NULL;
			free_tmp->value = NULL;
			free(free_tmp);
		}
		else
		{
			while (tmp->next)
			{
				if (ft_strncmp(tmp->next->key, command[i], ft_strlen(command[i])) == 0)
				{
					free_tmp = tmp->next;
					tmp->next = tmp->next->next;
					free_tmp->key = NULL;
					free_tmp->value = NULL;
					free(free_tmp);
					break ;
				}
				tmp = tmp->next;
			}
		}
		i++;
	}
}