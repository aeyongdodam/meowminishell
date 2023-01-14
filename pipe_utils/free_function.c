/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:25 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:10:31 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe(t_pipe *pi, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		free(pi->fd[i]);
		i++;
	}
	free(pi->fd);
}

void	free_split(char **split_path)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		free(split_path[i]);
		i++;
	}
	free(split_path);
}
