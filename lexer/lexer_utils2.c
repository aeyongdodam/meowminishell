/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:10:24 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/13 16:10:27 by mkwon            ###   ########.fr       */
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

char	*re_str_join(char **str, char **s)
{
	char	*temp;

	temp = ft_strjoin(*str, *s);
	free(*str);
	return (temp);
}

void	empty_line(char **line)
{
	if (!(**line))
		(*line)--;
}

void	empty_quote(t_node *node, char **str, char **s, int cash)
{
	if ((*s)[0] == 0 && cash == 1)
		return ;
	else if ((*s)[0] == 0 && (*str)[0] != 0)
		return ;
	else if ((*s)[0] == 0)
		save_token(node, "", WORD);
	else
		*str = re_str_join(str, s);
}
