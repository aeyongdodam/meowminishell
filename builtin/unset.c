
#include "../minishell.h"

int   builtin_unset(t_envnode *envnode, char **command)
{
	t_envnode *tmp;
	tmp = envnode;
	t_envnode *free_tmp;

	int     i;

	i = 1;
	if (!command[1])
		return (0);
	while (command[i])
	{
		while (tmp->next)
		{
			if (ft_strncmp(tmp->next->key, command[i], ft_strlen(command[i])) == 0)
			{
				free_tmp = tmp->next;
				tmp->next = tmp->next->next;
				free(free_tmp->key);
				free(free_tmp->value);
				free_tmp->key = NULL;
				free_tmp->value = NULL;

				free(free_tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}