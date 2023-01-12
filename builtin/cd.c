
#include "../minishell.h"

char	*find_home(t_envnode *envnode)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "HOME", 4) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char *find_oldpwd(t_envnode *envnode)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 7) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
void update_oldpwd(t_envnode *envnode, char *s)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
		{
			tmp->value = ft_strdup(s);		
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
	if (ch == -1 && last_flag != 1)
	{
		update_oldpwd(envnode, "");
		write(2, "meowshell: cd: ", 15);
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory\n", 29);
		return (-1);
	}
	return (0);
}

void builtin_cd(char **command, t_envnode *envnode , int last_flag)
{
	char	buf[255];
	char	next[255];

	char	*home;
	char 	*oldpwd;
	int		ch;
	int		i;
	int		flag;
	int		error;
	t_envnode *tmp;
	tmp = envnode;

	//cd 하나만 있는 경우
	if (!command[1])
	{
		home = find_home(envnode); // HOME 값 받아옴
		getcwd(buf, 255);
		ch = chdir(home);
		update_oldpwd(envnode, buf);
		if (ch == -1 && last_flag == 1)
		{
			update_oldpwd(envnode, "");
			write(2, "meowshell: cd: HOME not set\n", 29);
		}
	}
	else if (ft_strncmp(command[1], "--", 3) == 0) //특수문자 오는경우
	{
		i = 1;
		home = find_home(envnode);
		if (command[2])
		{
			if (ft_strncmp(command[2], "-", 2) == 0)
			{
				oldpwd = find_oldpwd(envnode);
				getcwd(buf, 255);
				ch = chdir(oldpwd);
				if (ch == -1)
				{
					update_oldpwd(envnode, "");
					write(2, "meowshell: cd: OLDPWD not set\n", 31);
				}
				else
				{
					update_oldpwd(envnode, buf);
					if (last_flag == 1)
						printf("%s\n",buf);
				}
			}					
			else
				find_cd_path(command[2], buf, envnode, last_flag);
		}
		else
		{
			getcwd(buf, 255);
			ch = chdir(home);
			update_oldpwd(envnode, buf);
			if (ch == -1 && last_flag != 1)
			{
				update_oldpwd(envnode, "");
				write(2, "meowshell: cd: HOME not set\n", 29);				
			}
		}
	}
	else if (ft_strncmp(command[1], "-", 2) == 0) //특수문자 오는경우
	{
		oldpwd = find_oldpwd(envnode);
		getcwd(buf, 255);
		ch = chdir(oldpwd);
		update_oldpwd(envnode, buf);
		if (last_flag == 1)
			printf("%s\n",buf);
		if (ch == -1 && last_flag == 1)
		{
			update_oldpwd(envnode, "");
			write(2, "meowshell: cd: OLDPWD not set\n", 31);
		}
	}
	else
		error = find_cd_path(command[1], buf, envnode, last_flag);
}