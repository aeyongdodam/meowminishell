/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:21 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:23 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

int	ft_newlinecmp(char *s)
{
	int	i;

	i = 2;
	if (s[0] == '-' && s[1] == 'n')
	{
		while (s[i] == 'n')
			i++;
		if ((int)ft_strlen(s) == i)
			return (1);
	}
	return (0);
}

void	builtin_echo(char **command)
{
	int		newline_flag;
	int		i;

	newline_flag = 0;
	i = 1;
	if (!command[1])
	{
		printf("\n");
		return ;
	}
	if (ft_newlinecmp(command[i]) == 1)
		newline_flag = 1;
	while (ft_newlinecmp(command[i]) == 1)
		i++;
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	if (newline_flag == 0)
		printf("\n");
}
