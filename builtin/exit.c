#include "../minishell.h"

int	num_check(char *s)
{
	int			i;
	int			label;
	long long	num;

	i = 0;
	num = 0;
	label = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			label = label * (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0');
		if (num > 2147483647 || num < -2147483648)
			return (0);
		i++;
	}
	if (i == ft_strlen(s))
		return (1);
	else
		return (0);
}

int	exit_utils(char **command, int last_flag)
{
	if (num_check(command[1]) == 0)
	{
		if (last_flag != 1)
		{
			write(2, "exit\n", 5);
			write(2, "meowshell: exit: ", 18);
			write(2, command[1], ft_strlen(command[1]));
			write(2, " numeric argument required\n", 28);
		}
		return (1);
	}
	if (last_flag == 1)
		write(2, "exit\n", 6);
	return (0);
}

int	builtin_exit(char **command, int last_flag)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!command[1])
	{
		if (last_flag != 1)
			write(2, "exit\n", 5);
		exit(0);
	}
	else if (command[2])
	{
		if (last_flag != 1)
			write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	else if (command[1])
	{
		if (exit_utils(command, last_flag))
			exit (255);
	}
	exit(ft_atoi(command[1]));
}
