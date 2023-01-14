/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:34:09 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/14 21:34:17 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prt_cd_error(t_envnode *envnode, int flag)
{
	update_oldpwd(envnode, "");
	if (flag == 1)
		write(2, "meowshell: cd: HOME not set\n", 29);
	else if (flag == 2)
		write(2, "meowshell: cd: OLDPWD not set\n", 31);
}

int	cd_one_cmd(t_envnode *envnode, int last_flag, char *buf)
{
	char	*home;
	int		ch;

	home = find_home(envnode);
	getcwd(buf, 255);
	ch = chdir(home);
	update_oldpwd(envnode, buf);
	if (ch == -1 && last_flag != 1)
	{
		prt_cd_error(envnode, 1);
		return (1);
	}
	return (0);
}

int	cd_cmd2(char **command, t_envnode *envnode, int last_flag, char *buf)
{
	char	*oldpwd;
	int		ch;

	if (ft_strncmp(command[2], "-", 2) == 0)
	{
		oldpwd = find_oldpwd(envnode);
		getcwd(buf, 255);
		ch = chdir(oldpwd);
		if (ch == -1)
		{
			if (last_flag != 1)
				prt_cd_error(envnode, 2);
			return (1);
		}
		else
		{
			update_oldpwd(envnode, buf);
			if (last_flag == 1)
				printf("%s\n", buf);
		}
	}					
	else
		return (find_cd_path(command[2], buf, envnode, last_flag));
	return (0);
}

int	cd_home(char **command, t_envnode *envnode, int last_flag, char *buf)
{
	char	*home;
	int		ch;

	home = find_home(envnode);
	if (command[2])
		cd_cmd2(command, envnode, last_flag, buf);
	else
	{
		getcwd(buf, 255);
		ch = chdir(home);
		update_oldpwd(envnode, buf);
		if (ch == -1 && last_flag != 1)
		{
			prt_cd_error(envnode, 1);
			return (1);
		}
	}
	return (0);
}

int	cd_oldpwd(t_envnode *envnode, int last_flag, char *buf)
{
	char	*home;
	char	*oldpwd;
	int		ch;

	oldpwd = find_oldpwd(envnode);
	getcwd(buf, 255);
	ch = chdir(oldpwd);
	update_oldpwd(envnode, buf);
	if (ch != -1 && last_flag != 1)
		printf("%s\n", buf);
	if (ch == -1 && last_flag != 1)
	{
		update_oldpwd(envnode, "");
		write(2, "meowshell: cd: OLDPWD not set\n", 31);
		return (1);
	}
	return (0);
}
