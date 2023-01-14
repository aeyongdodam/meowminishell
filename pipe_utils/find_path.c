/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:17 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:46:31 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_env_path(t_envnode *tmp, char **save_path)
{
	while (tmp != 0)
	{
		if (ft_strncmp("PATH", tmp->key, 4) == 0)
		{
			if (tmp->value)
				*save_path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

char	*split_path(char *save_path, char *s)
{
	char	**split_path;
	char	*for_free;
	char	*ret;
	int		i;

	split_path = ft_split(save_path, ':');
	free(save_path);
	i = 0;
	while (split_path[i])
	{
		for_free = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		free(for_free);
		for_free = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], s);
		free(for_free);
		if (access(split_path[i], X_OK) == 0)
			ret = ft_strdup(split_path[i]);
		i++;
	}
	free_split(split_path);
	return (ret);
}

char	*find_path(t_envnode *envnode, char *s)
{
	t_envnode	*tmp;
	char		*for_free;
	char		*save_path;
	char		*ret;

	ret = NULL;
	tmp = envnode;
	save_path = NULL;
	find_env_path(tmp, &save_path);
	if (!save_path)
		return (ret);
	if (!save_path[0])
		return (ret);
	for_free = save_path;
	save_path = ft_substr(save_path, 5, ft_strlen(save_path));
	free(for_free);
	ret = split_path(save_path, s);
	return (ret);
}
