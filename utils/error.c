/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:13:19 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/13 16:13:21 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_flag(t_node *node, t_token *token)
{
	if (token->flag == PIPE)
	{
		if (error_pipe(node))
			return (1);
	}
	if (token->flag == REDI || token->flag == HERE)
	{
		if (error_redi(token))
			return (1);
	}
	if (token->flag == WORD)
	{
		if (error_quote(token))
			return (1);
	}
	return (0);
}

int	check_tree(t_node *node)
{
	t_token	*token;

	if (node->token->flag == ROOT)
	{
		if (node->right_child != NULL && \
		node->right_child->token->flag == PIPE && \
		node->left_child == NULL)
		{
			prt_error(1, node->right_child->token->str);
			return (1);
		}
	}
	if (node->left_child != NULL && check_tree(node->left_child))
		return (1);
	if (node->right_child != NULL && check_tree(node->right_child))
		return (1);
	token = node->token;
	while (token)
	{
		if (error_flag(node, token))
			return (1);
		token = token->next;
	}
	return (0);
}

int	find_error(t_tree *tree, char *line)
{
	t_node	*node;

	node = tree->root;
	if (tree->root->left_child == NULL && tree->root->right_child == NULL)
		return (1);
	add_history(line);
	if (check_tree(node))
		return (1);
	if (input_exit(tree))
		prt_exit();
	return (0);
}
