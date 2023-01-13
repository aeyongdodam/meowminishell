#include "../minishell.h"

int builtin_exit(char **command, int last_flag)
{
    int i = 0;
    if (!command[1])
    {
        return (0);
    }
    else if (command[1])
    {
        while (command[1][i])
        {
            if (command[1][i] < '0' || command[1][i] > '9' && last_flag != 1)
            {
                write(2, "exit\n", 5);
                write(2, "meowshell: exit: ", 18);
                write(2, command[1], ft_strlen(command[1]));
                write(2, " numeric argument required\n", 28);;
                return (255);
            }
        i++;
        }
    }
    else if (command[2])
    {
        write(2, "exit: too many arguments\n", 26);
        return (1);
    }
    return (ft_atoi(command[1]));
}