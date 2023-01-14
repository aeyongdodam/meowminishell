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

extern int	g_exit_code;

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
	free(str2);
	envstr = ft_calloc(1, 1);
	envstr[0] = 0;
	return (envstr);
}

int	dallor_save(t_node *node, char **line, char **str, t_tree *tree)
{
	char	*s;

	if (*(*line + 1) == 0)
	{
		save_token(node, "$", WORD);
		*str = re_str(*str);
		return (1);
	}
	else if (*(*line + 1) == '?')
	{
		s = ft_itoa(g_exit_code);
		*str = re_str_join(str, &s);
		free(s);
		(*line)++;
		set_variable(tree, 0, 0, 0);
		return (1);
	}
	else if (get_type(*line + 1) != WORD || *(*line + 1) == ' ')
	{
		*str = str_one_join(*str, '$', tree, 1);
		return (1);
	}
	return (0);
}

int	check_dallor(t_node *node, char **line, char **str, t_tree *tree)
{
	char		*str2;

	if (dallor_save(node, line, str, tree))
		return (1);
	str2 = ft_calloc(1, 1);
	(*line)++;
	while (**line)
	{
		str2 = str_one_join(str2, (*line)[0], tree, 1);
		if (*(*line + 1) == 0 || *(*line + 1) == '$' || \
		get_type(*line + 1) != WORD || *(*line + 1) == ' ')
			break ;
		(*line)++;
	}
	str2 = change_env(str2, tree->env);
	*str = re_str_join(str, &str2);
	free(str2);
	set_variable(tree, 0, 0, 0);
	return (1);
}
