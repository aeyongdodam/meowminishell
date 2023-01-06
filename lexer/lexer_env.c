/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:53:49 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/06 15:53:51 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_env(char *str2, t_envnode *envnode)
{
	char		*envstr;
	t_envnode	*node;

	node = envnode;
	while (node)
	{
		if (ft_strncmp(node->key, str2, ft_strlen(str2) + 1) == 0)
		{
			envstr = ft_strdup(node->value);
			free(str2);
			return (envstr);
		}
		node = node->next;
	}
	envstr = malloc(1);
	envstr[0] = 0;
	return (envstr);
}

void	check_dallor(t_node *node, char **line, char **str, t_tree *tree)
{
	char		*str2;

	str2 = malloc(1);
	str2[0] = 0;
	if (*(*line + 1) == 0)
	{
		save_token(node, "$", WORD);
		*str = re_str(*str);
		free(str2);
		return ;
	}
	else if (get_type(*line + 1) != WORD || *(*line + 1) == ' ')
	{
		*str = str_one_join(*str, '$', tree);
		free(str2);
		(*line)++;
		return ;
	}
	(*line)++;
	while (**line)
	{
		if (get_type(*line) != WORD || **line == ' ')
			break ;
		str2 = str_one_join(str2, (*line)[0], tree);
		(*line)++;
	}
	str2 = change_env(str2, tree->env);
	*str = ft_strjoin(*str, str2);
}
