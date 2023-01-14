/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:39:31 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:25:08 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_export(t_envnode **node)
{
	t_envnode	*temp;

	while (*node)
	{
		temp = *node;
		*node = (*node)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	prt_export(t_envnode *envnode, int last_flag)
{
	t_envnode	*node;

	node = init_temp_env(envnode, 0);
	sort_env(&node);
	if (last_flag != 1)
	{
		while (node)
		{
			printf("declare -x %s", node->key);
			if (node->value)
				printf("=\"%s\"\n", node->value);
			else
				printf("\n");
			node = node->next;
		}
	}
	free_export(&node);
}

t_envnode	*init_new_export(void)
{
	t_envnode	*new_node;

	new_node = malloc(sizeof(t_envnode));
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->key = NULL;
	new_node->value = NULL;
	return (new_node);
}

void	export_find(t_envnode **node, t_envnode **tmp, char **key, char **value)
{
	(*node)->key = *key;
	(*node)->value = *value;
	(*tmp)->next = *node;
	*tmp = (*tmp)->next;
}

void	export_new(t_envnode **node, t_envnode **tmp, char **key)
{
	(*node)->key = *key;
	(*node)->value = NULL;
	(*tmp)->next = *node;
	*tmp = (*tmp)->next;
}
