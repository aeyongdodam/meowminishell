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

int	get_type(char *line)
{
	if (*line == '<' && *(line + 1) == '<')
		return (HERE);
	else if (*line == '>' && *(line + 1) == '>')
		return (REDI);
	else if (*line == '<')
		return (REDI);
	else if (*line == '>')
		return (REDI);
	else if (*line == '|')
		return (PIPE);
	else if (*line == '\"')
		return (QUOTE_D);
	else if (*line == '\'')
		return (QUOTE_S);
	return (WORD);
}

char	*str_one_join(char *s1, char c, t_tree *tree)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s1);
	if (tree != 0)
		set_variable(tree, 0, 0, 0);
	return (str);
}

char	*re_str(char *str)
{
	free(str);
	str = malloc(1);
	str[0] = 0;
	return (str);
}

void	set_variable(t_tree *tree, int space, int pipe, int quote)
{
	tree->space = space;
	tree->pipe = pipe;
	tree->double_quote = quote;
	tree->single_quote = quote;
}

void	set_lexer(t_node **node, t_tree **tree, char **str, t_envnode *env)
{
	*str = malloc(1);
	(*str)[0] = 0;
	*tree = init_tree();
	(*tree)->env = env;
	*node = (*tree)->root;
	(*node)->token->flag = 0;
}
