/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:09:51 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 00:26:37 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	pipe_prt_error(int error_code, char *s)
{
	if (error_code == 1)
	{
		write(2, "meowshell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 21);
		exit (1);
	}
	else if (error_code == 2)
	{
		write(2, "meowshell: pipe open error\n", 28);
		g_exit_code = 1;
	}
	else if (error_code == 3)
	{
		write(2, "meowshell: fork error\n", 23);
		g_exit_code = 1;
	}
	else if (error_code == 4)
	{
		write(2, "meowshell: dup error\n", 22);
		exit (1);
	}
}

void	check_stat(char *s)
{
	struct stat	buf;

	if (stat(s, &buf) == -1)
	{
		write(2, "meowshell: ", 12);
		write(2, s, ft_strlen(s));
		write(2, " : No such file or directory\n", 30);
		exit(1);
	}
}
