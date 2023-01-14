/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:12 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:15 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home(t_envnode *envnode)
{
	t_envnode	*tmp;

	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "HOME", 4) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_oldpwd(t_envnode *envnode)
{
	t_envnode	*tmp;

	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_oldpwd(t_envnode *envnode, char *s)
{
	t_envnode	*tmp;
	char		*for_free;

	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
		{
			for_free = tmp->value;
			tmp->value = ft_strdup(s);
			free(for_free);
			break ;
		}
		tmp = tmp->next;
	}
}

int	find_cd_path(char *s, char *buf, t_envnode *envnode, int last_flag)
{
	int	ch;

	getcwd(buf, 255);
	ch = chdir(s);
	update_oldpwd(envnode, buf);
	if (ch == -1)
	{
		if (last_flag != 1)
		{
			update_oldpwd(envnode, "");
			write(2, "meowshell: cd: ", 15);
			write(2, s, ft_strlen(s));
			write(2, ": No such file or directory\n", 29);
		}
		return (1);
	}
	return (0);
}

int	builtin_cd(char **command, t_envnode *envnode, int last_flag)
{
	char	buf[255];
	int		error;

	error = 0;
	if (!command[1])
		error = cd_one_cmd(envnode, last_flag, buf);
	else if (ft_strncmp(command[1], "--", 3) == 0)
		error = cd_home(command, envnode, last_flag, buf);
	else if (ft_strncmp(command[1], "-", 2) == 0)
		error = cd_oldpwd(envnode, last_flag, buf);
	else
		error = find_cd_path(command[1], buf, envnode, last_flag);
	return (error);
}
