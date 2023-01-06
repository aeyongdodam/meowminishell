/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:50:56 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/06 15:50:59 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_token(t_node *node, char *str, int flag)
{
	t_token	*token;

	if (node->left_child == NULL)
	{
		node->left_child = init_node();
		token = node->left_child->token;
		token->str = ft_strdup(str);
		token->flag = flag;
	}
	else
	{
		token = node->left_child->token;
		while (token->next)
			token = token->next;
		token->next = init_token();
		token->next->prev = token;
		token->next->str = ft_strdup(str);
		token->next->flag = flag;
	}
}

void	word_token(t_node *node, char *str, t_tree *tree)
{
	if (tree->space == 0 && str[0] != 0)
	{
		save_token(node, str, WORD);
		str = re_str(str);
		set_variable(tree, 1, 0, 0);
	}
}

t_node	*pipe_token(t_node *node, char *str, t_tree *tree)
{
	if (tree->pipe == 1)
	{
		exit(1);
	}
	if (tree->space == 0 && str[0] != 0)
	{
		save_token(node, str, WORD);
		str = re_str(str);
	}
	node->right_child = init_node();
	node->right_child->token->flag = PIPE;
	node->right_child->token->str = ft_strdup("|");
	node = node->right_child;
	set_variable(tree, 0, 1, 0);
	tree->pipe_cnt++;
	return (node);
}

void	redi_token(t_node *node, char **line, char *str, t_tree *tree)
{
	if (tree->space == 0 && str[0] != 0)
	{
		save_token(node, str, WORD);
		str = re_str(str);
	}
	if (**line == '<' && *(*line + 1) == '<')
	{
		save_token(node, "<<", HERE);
		(*line)++;
	}
	else if (**line == '>' && *(*line + 1) == '>')
	{
		save_token(node, ">>", REDI);
		(*line)++;
	}
	else if (**line == '<')
		save_token(node, "<", REDI);
	else if (**line == '>')
		save_token(node, ">", REDI);
}

void	check_quote(t_node *node, char **line, char **str, t_tree *tree)
{
	int	flag;

	if (**line == '\"')
		flag = QUOTE_D;
	else if (**line == '\'')
		flag = QUOTE_S;
	(*line)++;
	while (**line)
	{
		if (flag == 4 && **line == '$')
			check_dallor(node, line, str, tree);
		if (get_type(*line) == flag)
			break ;
		*str = str_one_join(*str, (*line)[0], tree);
		(*line)++;
	}
	if (str[0] != 0 && *(*line + 1) == 0)
	{
		save_token(node, *str, WORD);
		*str = re_str(*str);
	}
}
