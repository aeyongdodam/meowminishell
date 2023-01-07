
#include "../minishell.h"

int	ft_newlinecmp(char *s)
{
	int	i = 2;

	if (s[0] == '-' && s[1] == 'n')
	{
		while(s[i] == 'n')
			i++;
		if (ft_strlen(s) == i)
			return (1);
	}
	return (0);
}

void builtin_echo(char **command)
{
	t_token *tmp;
	int	newline_flag;

	newline_flag = 0;
	int i = 1;

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
