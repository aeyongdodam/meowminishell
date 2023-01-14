/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:35 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:38 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void prt_env(t_envnode *envnode)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0)
		{
			if (tmp->value == NULL)
				continue;
		}
		printf("tmp %s %p\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int 	find_key(char *key_tmp, char *value_tmp, t_envnode *envnode)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(key_tmp, tmp->key, ft_strlen(key_tmp)) == 0)
		{
			if (value_tmp != NULL)
			{
				tmp->value = value_tmp;
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
		if ((s[i] >= 'A' && s[i] < 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == '_' || s[i] == '=' || s[i] == '/' || s[i] == ':' || s[i] == '.')
		{
			i++;
			continue;
		}
		else
			return (-1);
		i++;
	}
	return (0);
}

t_envnode	*init_temp_env(t_envnode *envnode)
{
	t_envnode	*start;
	t_envnode	*origin;
	t_envnode	*node;
	t_envnode	*temp;

	origin = envnode;
	start = 0;
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

void	free_export(t_envnode **node)
{
	t_envnode	*temp;

	while (*node)
	{
		temp = *node;
		*node = (*node)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	prt_export(t_envnode *envnode, int last_flag)
{
	t_envnode	*node;
	node = init_temp_env(envnode);
	sort_env(&node);
	if (last_flag != 1)
	{
		while (node)
		{
			printf("declare -x %s", node->key);
			if (node->value)
				printf("=\"%s\"\n", node->value);
			else
				printf("\n");
			node = node->next;
		}
	}
	free_export(&node);
}

int    builtin_export(t_envnode *envnode, char **command, int last_flag)
{
	t_envnode *tmp;
	tmp = envnode;
	t_envnode *new_node;
	char *key_tmp;
	char *value_tmp;
	int j;
	if (!command[1])
		prt_export(envnode->next, last_flag);
	else if (last_flag == 1)
	{
		int	i = 1;
		int err;
		while (command[i])
		{
			err = check_export_err(command[i]);
			if (err == -1)
			{
				write(2, "meowshell: not a valid identifier\n", 35);
				return (1);
			}
			while (tmp->next)
				tmp = tmp->next;
			new_node = malloc(sizeof(t_envnode));
			new_node->next = NULL;
			new_node->prev = NULL;
			new_node->key = NULL;
			new_node->value = NULL;
			if (ft_strrchr(command[i], '=') != 0)
			{
				j = 0;
				while (command[i][j] != '=')
					j++;
				
				key_tmp = ft_substr(command[i], 0, j);
				value_tmp = ft_substr(command[i], j + 1, ft_strlen(command[i]));
				if (find_key(key_tmp, value_tmp, envnode) == 0) //값이 없어서 갱신해야할 때
				{
					new_node->key = key_tmp;
					new_node->value = value_tmp;
					tmp->next = new_node;
					tmp = tmp->next;
				}
			}
			else
			{
				key_tmp = command[i];
				if (find_key(key_tmp, NULL, envnode) == 0)
				{
					new_node->key = ft_strdup(key_tmp);
					new_node->value = NULL;
					tmp->next = new_node;
					tmp = tmp->next;
				}
			}
			i++;
	}
	}
	return (0);
}