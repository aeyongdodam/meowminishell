/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:26 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:29 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_envnode *envnode, char **command, int last_flag)
{
	t_envnode	*tmp;

	tmp = envnode;
	if (command[1])
	{
		if (last_flag == 0)
			write(2, "command error\n", 15);
		return (127);
	}
	else if (last_flag == 0)
	{
		while (tmp)
		{
			if (tmp->value != NULL)
			{
				printf("%s", tmp->key);
				printf("=");
				printf("%s\n", tmp->value);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
