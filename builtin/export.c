
#include "../minishell.h"

void prt_env(t_envnode *envnode)
{
	t_envnode *tmp;
	tmp = envnode;
	while (tmp)
	{
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
		if (ft_strncmp(key_tmp, tmp->key, ft_strlen(key_tmp)) == 0) //이미 있는 값을 갱신시킬때
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
		if (i == 0 && s[i] == '=')
			return (-1);
		if ((s[i] >= 'A' && s[i] < 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == '_' || s[i] == '=')
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

void    builtin_export(t_envnode *envnode, char **command, int last_flag)
{
	t_envnode *tmp;
	tmp = envnode;
	t_envnode *new_node;
	char *key_tmp;
	char *value_tmp;
	int j;
	if (!command[1])
	{
		tmp = tmp->next;
		if (last_flag != 1)
		{
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
			{
				printf("=\"%s\"\n", tmp->value);
			}
			else
				printf("\n");
			tmp = tmp->next;
		}
		}
	}
	else if (last_flag == 1)
	{
		int	i = 1;
		int err;
		while (command[i])
		{
			err =check_export_err(command[i]);
			if (err == -1)
			{
				write(2, "meowshell: not a valid identifier\n", 35);
				return ;
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

}