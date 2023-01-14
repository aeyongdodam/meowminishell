/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:57:32 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/06 15:57:34 by mkwon            ###   ########.fr       */
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

t_tree	*lexer(char	*line, t_envnode *envnode)
{
	t_tree	*tree;
	t_node	*node;
	char	*str;

	set_lexer(&node, &tree, &str, envnode);
	while (*line)
	{
		if (*line == '$')
			check_dallor(node, &line, &str, tree);
		else if (*line == ' ')
			word_token(node, &str, tree);
		else if (get_type(line) == PIPE)
			node = pipe_token(node, &str, tree);
		else if (get_type(line) == REDI || get_type(line) == HERE)
			redi_token(node, &line, &str, tree);
		else if (get_type(line) == QUOTE_D || get_type(line) == QUOTE_S)
			check_quote(node, &line, &str, tree);
		else
			str = str_one_join(str, line[0], tree, 1);
		line++;
	}
	if (str[0] != 0)
		save_token(node, str, WORD);
	return (tree);
}
