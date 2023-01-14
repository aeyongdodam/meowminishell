/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:11:09 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:11:13 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redi(t_node *tr)
{
	int		flag;
	t_token	*tmp;

	flag = 0;
	tmp = tr->left_child->token;
	while (tmp)
	{
		if (tmp->flag != 1)
		{
			if (ft_strncmp(tmp->str, ">", 2) == 0 || \
			ft_strncmp(tmp->str, "<", 2) == 0 || \
			ft_strncmp(tmp->str, ">>", 3) == 0 || \
			ft_strncmp(tmp->str, "<<", 3) == 0)
			flag = 1;
		}
		tmp = tmp->next;
	}
	return (flag);
}

int	redi_command_count(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (tmp->flag != 1)
		{
			if (ft_strncmp(tmp->str, "<", 2) == 0 || \
			ft_strncmp(tmp->str, ">>", 3) == 0 || \
			ft_strncmp(tmp->str, ">", 2) == 0 || \
			ft_strncmp(tmp->str, "<<", 3) == 0)
				i -= 2;
		}
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**save_redi_command(t_token *tmp, int i)
{
	char	**save_command;
	int		j;

	j = 0;
	save_command = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		if (tmp->flag != 1)
		{
			if (ft_strncmp(tmp->str, "<", 2) == 0 \
			|| ft_strncmp(tmp->str, ">>", 3) == 0 || \
			ft_strncmp(tmp->str, ">", 2) == 0 || \
			ft_strncmp(tmp->str, "<<", 3) == 0)
				tmp = tmp->next->next;
		}
		save_command[j] = ft_strdup(tmp->str);
		tmp = tmp->next;
		j++;
	}
	save_command[j] = NULL;
	return (save_command);
}