/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:16:44 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/13 16:16:47 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	prt_error(int flag, char *str)
{
	if (flag == 1)
		printf("meowshell: syntax error near unexpected token '%s'\n", str);
	else if (flag == 2)
		printf("meowshell: syntax error near unexpected token 'newline'\n");
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

int	error_pipe(t_node *node)
{
	if (ft_strncmp(node->token->str, "||", 3) == 0)
	{
		if (check_pipe(node, 2))
			prt_error(1, node->token->str);
		else if (ft_strncmp(node->right_child->token->str, "|", 2) == 0)
			prt_error(1, node->right_child->token->str);
		return (1);
	}
	if (node->left_child == NULL)
	{
		if (check_pipe(node, 1))
			prt_error(1, node->token->str);
		else if (ft_strncmp(node->right_child->token->str, "||", 3) == 0)
			prt_error(1, node->right_child->token->str);
		return (1);
	}
	return (0);
}

int	error_redi(t_token *token)
{
	if (token->next == NULL)
	{
		prt_error(2, 0);
		return (1);
	}
	else if (token->next->flag == REDI || token->next->flag == HERE)
	{
		prt_error(1, token->next->str);
		return (1);
	}
	return (0);
}

int	error_quote(t_token *token)
{
	if (ft_strncmp(token->str, "\"", 2) == 0 || \
	ft_strncmp(token->str, "\'", 2) == 0)
	{
		prt_error(1, token->str);
		return (1);
	}
	return (0);
}
