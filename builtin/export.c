/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:35 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:42:19 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_cmd(t_envnode *envnode, t_envnode *tmp, char **command, int i)
{
	t_envnode	*new_node;
	char		*key_tmp;
	char		*value_tmp;
	int			j;

	new_node = init_new_export();
	if (ft_strrchr(command[i], '=') != 0)
	{
		j = 0;
		while (command[i][j] != '=')
			j++;
		key_tmp = ft_substr(command[i], 0, j);
		value_tmp = ft_substr(command[i], j + 1, ft_strlen(command[i]));
		if (find_key(key_tmp, value_tmp, envnode) == 0)
			export_find(&new_node, &tmp, &key_tmp, &value_tmp);
		else
			free(new_node);
	}
	else
	{
		key_tmp = command[i];
		if (find_key(key_tmp, NULL, envnode) == 0)
			export_new(&new_node, &tmp, &key_tmp);
		else
			free(new_node);
	}
}

int	builtin_export(t_envnode *envnode, char **command, int last_flag)
{
	t_envnode	*tmp;
	int			i;
	int			err;

	tmp = envnode;
	if (!command[1])
		prt_export(envnode->next, last_flag);
	else if (last_flag == 1)
	{
		i = 1;
		while (command[i])
		{
			err = check_export_err(command[i]);
			if (err == -1)
			{
				write(2, "meowshell: not a valid identifier\n", 35);
				return (1);
			}
			while (tmp->next)
				tmp = tmp->next;
			export_cmd(envnode, tmp, command, i);
			i++;
		}
	}
	return (0);
}
