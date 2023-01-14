/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:39:24 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:39:31 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prt_env(t_envnode *envnode)
{
	t_envnode	*tmp;

	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0)
		{
			if (tmp->value == NULL)
				continue ;
		}
		printf("tmp %s %p\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	find_key(char *key_tmp, char *value_tmp, t_envnode *envnode)
{
	t_envnode	*tmp;
	char		*temp;

	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(key_tmp, tmp->key, ft_strlen(key_tmp)) == 0)
		{
			if (value_tmp != NULL)
			{
				temp = tmp->value;
				tmp->value = value_tmp;
				free(temp);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_export_err(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (i == 0 && (s[i] == '=' || s[i] == ':' || s[i] == '.'))
			return (-1);
		if ((s[i] >= 'A' && s[i] < 'Z') || (s[i] >= 'a' && s[i] <= 'z') || \
		s[i] == '_' || s[i] == '=' || s[i] == '/' || s[i] == ':' || s[i] == '.')
		{
			i++;
			continue ;
		}
		else
			return (-1);
		i++;
	}
	return (0);
}

t_envnode	*init_temp_env(t_envnode *envnode, t_envnode *start)
{
	t_envnode	*origin;
	t_envnode	*node;
	t_envnode	*temp;

	origin = envnode;
	while (origin)
	{
		node = ft_calloc(1, sizeof(t_envnode));
		node->prev = 0;
		node->next = 0;
		node->key = ft_strdup(origin->key);
		if (origin->value)
			node->value = ft_strdup(origin->value);
		if (!start)
			start = node;
		else
		{
			temp->next = node;
			node->prev = temp;
		}
		temp = node;
		origin = origin->next;
	}
	return (start);
}

void	sort_env(t_envnode **envnode)
{
	t_envnode	*i;
	t_envnode	*j;
	char		*temp;

	i = *envnode;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp(i->key, j->key, ft_strlen(i->key)) > 0)
			{
				temp = i->key;
				i->key = j->key;
				j->key = temp;
				temp = i->value;
				i->value = j->value;
				j->value = temp;
			}
			j = j->next;
		}
		i = i->next;
	}
}
