/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:48:13 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/06 15:48:18 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_variable(t_tree *tree, int space, int pipe, int redi)
{
	tree->space = space;
	tree->pipe = pipe;
	tree->redi = redi;
}

void	set_lexer(t_node **node, t_tree **tree, char **str, t_envnode *env)
{
	*str = ft_calloc(1, 1);
	*tree = init_tree();
	(*tree)->env = env;
	*node = (*tree)->root;
	(*node)->token->flag = 0;
}

void	set_quote(int *cash, int *flag, char **s, char **line)
{
	*cash = 0;
	*flag = get_type(*line);
	*s = ft_calloc(1, 1);
	(*line)++;
}

void	double_redi(t_node *node, char **line, char **str, t_tree *tree)
{
	set_variable(tree, 0, 0, 0);
	redi_token(node, line, str, tree);
}

void	save_quote(t_node *node, char **str, t_tree *tree, int flag)
{
	if (tree->space == 0 && *str[0] != 0)
	{
		save_token(node, *str, WORD);
		*str = re_str(*str);
		set_variable(tree, 1, 0, 0);
	}
	if (flag == QUOTE_D)
	{
		save_token(node, "\"", WORD);
		*str = re_str(*str);
	}
	else if (flag == QUOTE_S)
	{
		save_token(node, "\'", WORD);
		*str = re_str(*str);
	}
}
