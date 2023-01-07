
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
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
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
			// printf("here tmp->value %s\n",tmp->value);			
			break ;
		}
		tmp = tmp->next;
	}
}
int	find_cd_path(char *s, char *buf, t_envnode *envnode)
{
	int	ch;
	getcwd(buf, 255);
	ch = chdir(s);
	update_oldpwd(envnode, buf);
	if (ch == -1)
	{
		printf("PATH 오류\n");
		return (-1);
	}
	return (0);
}




void builtin_cd(char **command, t_envnode *envnode)
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
		// printf("이전 경로 %s\n",buf);
		update_oldpwd(envnode, buf);



		if (ch == -1)
			printf("에러 이동못함\n");
	}
	else if (ft_strncmp(command[1], "--", 2) == 0) //특수문자 오는경우
	{
		i = 1;
		home = find_home(envnode);
		if (home == NULL)
		{
			flag = -1;
			while (ft_strncmp(command[i], "--", 2) == 0)
				i++;
			if (ft_strncmp(command[i], "-", 1) == 0)
			{
				oldpwd = find_oldpwd(envnode);
				if (oldpwd == NULL)
				{
					flag = -1; // "--" "-" 둘 다 없는 경우니까이게
					while ((ft_strncmp(command[i], "--", 2) == 0 || ft_strncmp(command[i], "-", 1) == 0) && command[i])
						i++;
					if (command[i])
					{
						find_cd_path(command[i], buf, envnode);
					}
				}
				else
				{
					getcwd(buf, 255);

					ch = chdir(oldpwd);
					getcwd(buf, 255);
					printf("이전 경로 %s\n",buf);
					update_oldpwd(envnode, buf);
					if (ch == -1)
						printf("경로가 없는 error\n");
				}	
			}
		}
		else
		{
				getcwd(buf, 255);
				ch = chdir(home);
				update_oldpwd(envnode, buf);
			if (ch == -1)
				printf("경로가 없는 error\n");
		}
	}
	else if (ft_strncmp(command[1], "-", 1) == 0) //특수문자 오는경우
	{
		i = 1;
		oldpwd = find_oldpwd(envnode);
		if (oldpwd == NULL)
		{
			flag = -1;
			while (ft_strncmp(command[i], "-", 1) == 0)
				i++;
			if (ft_strncmp(command[i], "--", 2) == 0)
			{
				home = find_home(envnode);
				if (home == NULL)
				{
					flag = -1; // "--" "-" 둘 다 없는 경우니까이게
					while ((ft_strncmp(command[i], "--", 2) == 0 || ft_strncmp(command[i], "-", 1) == 0) && command[i])
						i++;
					if (command[i])
					{
						find_cd_path(command[i], buf, envnode);
					}
				}
				else
				{
				getcwd(buf, 255);

				ch = chdir(home);
				update_oldpwd(envnode, buf);
					if (ch == -1)
						printf("경로가 없는 error\n");
				}	
			}
		}
		else
		{
				getcwd(buf, 255);

				ch = chdir(oldpwd);

				update_oldpwd(envnode, buf);
				getcwd(buf, 255);	
				printf("이전 경로 %s\n",buf);
			if (ch == -1)
				printf("경로가 없는 error\n");
		}

		if (flag == -1)
			printf("변수가 없어서 생기는 에러 메세지\n");
	}
	else
	{
		printf("특수문자 아닐때\n");
		error = find_cd_path(command[1], buf, envnode);
	}
}