/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:47 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:51 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_free(t_envnode **tmp, t_envnode **free_tmp)
{
	*free_tmp = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	free((*free_tmp)->key);
	free((*free_tmp)->value);
	(*free_tmp)->key = NULL;
	(*free_tmp)->value = NULL;
	free(*free_tmp);
}

int	builtin_unset(t_envnode *envnode, char **command)
{
	t_envnode	*tmp;
	t_envnode	*free_tmp;
	int			i;

	tmp = envnode;
	i = 1;
	if (!command[1])
		return (0);
	while (command[i])
	{
		while (tmp->next)
		{
			if (ft_strncmp(tmp->next->key, command[i], \
			ft_strlen(command[i])) == 0)
			{
				unset_free(&tmp, &free_tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
