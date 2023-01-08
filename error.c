/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:29:02 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/08 01:29:07 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	prt_error(int flag)
{
	if (flag == 1)
		printf("meowshell: syntax error near unexpected token '|'\n");
	else if (flag == 2)
		printf("meowshell: syntax error near unexpected token '||'\n");
	else if (flag == 3)
		printf("meowshell: syntax error near unexpected token `newline'\n");
	g_exit_code = 258;
}

int	check_pipe(t_node *node, int flag)
{
	if (flag == 1)
	{
		if (node->right_child == NULL || \
		ft_strncmp(node->right_child->token->str, "|", 2) == 0)
			return (1);
	}
	else
	{
		if (node->right_child == NULL || \
		ft_strncmp(node->right_child->token->str, "||", 3) == 0)
			return (1);
	}
	return (0);
}

int	error_pipe(t_node *root)
{
	t_node	*node;

	node = root->right_child;
	while (node)
	{
		if (ft_strncmp(node->token->str, "||", 3) == 0)
		{
			if (check_pipe(node, 2))
				prt_error(2);
			else if (ft_strncmp(node->right_child->token->str, "|", 2) == 0)
				prt_error(1);
			return (1);
		}
		if (node->left_child == NULL)
		{
			if (check_pipe(node, 1))
				prt_error(1);
			else if (ft_strncmp(node->right_child->token->str, "||", 3) == 0)
				prt_error(2);
			return (1);
		}
		node = node->right_child;
	}
	return (0);
}

int	error_redi(t_node *node)
{
	t_token	*token;

	if (node->token->flag == WORD || node->token->flag == REDI)
	{
		token = node->token;
		while (token)
		{
			if (token->flag == REDI && token->next == NULL)
			{
				prt_error(3);
				return (1);
			}
			token = token->next;
		}
	}
	if (node->left_child != NULL)
		return (error_redi(node->left_child));
	if (node->right_child != NULL)
		return (error_redi(node->right_child));
	return (0);
}

int	find_error(t_tree *tree)
{
	t_node	*node;

	node = tree->root;
	if (tree->root->right_child != NULL && error_pipe(tree->root))
		return (1);
	if (error_redi(tree->root))
		return (1);
	if (input_exit(tree))
		prt_exit();
	return (0);
}
