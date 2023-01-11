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

char	*str_one_join(char *s1, char c, t_tree *tree, int flag)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = ft_calloc(len + 2, 1);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s1);
	if (flag == 1)
		set_variable(tree, 0, 0, 0);
	return (str);
}

char	*re_str(char *str)
{
	free(str);
	str = ft_calloc(1, 1);
	if (!str)
		return (0);
	return (str);
}

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

void	double_redi(t_node *node, char **line, char **str, t_tree *tree)
{
	set_variable(tree, 0, 0, 0);
	redi_token(node, line, str, tree);
}
