/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:15:39 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/12 23:15:42 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_node	*init_node(void)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->token = init_token();
	node->left_child = NULL;
	node->right_child = NULL;
	return (node);
}

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = ft_calloc(1, sizeof(t_tree));
	tree->root = init_node();
	tree->pipe_cnt = 0;
	tree->ridi_cnt = 0;
	tree->heredoc_cnt = 0;
	tree->space = 0;
	tree->pipe = 0;
	tree->redi = 0;
	return (tree);
}

t_envnode	*init_envnode(t_envnode	**head, char *str)
{
	t_envnode	*node;
	t_envnode	*tempnode;

	node = ft_calloc(1, sizeof(t_envnode));
	node->prev = 0;
	node->next = 0;
	node->key = ft_strdup(str);
	if (*head == NULL)
	{
		*head = ft_calloc(1, sizeof(t_envnode));
		(*head)->key = ft_strdup("HEAD");
		(*head)->prev = 0;
		(*head)->next = node;
		node->prev = (*head);
	}
	else
	{
		tempnode = *head;
		while (tempnode->next)
			tempnode = tempnode->next;
		tempnode->next = node;
		node->prev = tempnode;
	}
	return (node);
}

t_envnode	*init_env(char **envp, t_tree *tree)
{
	t_envnode	*head;
	t_envnode	*node;
	char		*str;
	int			i;
	int			j;

	set_init_env(&head, &str);
	i = -1;
	while (envp[++i] != 0)
	{
		j = -1;
		while (envp[i][++j] != 0)
		{
			if (envp[i][j] == '=')
			{
				node = init_envnode(&head, str);
				str = re_str(str);
			}
			else
				str = str_one_join(str, envp[i][j], tree, 0);
		}
		node->value = ft_strdup(str);
		str = re_str(str);
	}
	return (head);
}
