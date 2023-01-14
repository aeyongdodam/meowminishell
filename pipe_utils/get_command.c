/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:38 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:10:41 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_redi_command(t_node *tr)
{
	t_token	*tmp;
	int		i;
	char	**save_command;

	tmp = tr->left_child->token;
	i = redi_command_count(tmp);
	tmp = tr->left_child->token;
	save_command = save_redi_command(tmp, i);
	return (save_command);
}

char	**get_command(t_node *tr)
{
	int		i;
	int		j;
	char	**save_command;
	t_token	*tmp;

	tmp = tr->left_child->token;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	save_command = malloc(sizeof(char *) * (i + 1));
	tmp = tr->left_child->token;
	i = 0;
	while (tmp)
	{
		save_command[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	save_command[i] = 0;
	return (save_command);
}