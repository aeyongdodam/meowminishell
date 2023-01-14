#include "../minishell.h"

int builtin_exit(char **command, int last_flag)
{
    int i = 0;
    int flag = 0;
    if (!command[1])
    {
        if (last_flag != 1)
            write(2, "exit\n", 5);
        return (0);
    }
    else if (command[2])
    {
        if (last_flag != 1)
            write(2, "exit: too many arguments\n", 26);
        return (-1);
    }
    else if (command[1])
    {
        while (command[1][i])
        {
            if (command[1][i] < '0' || command[1][i] > '9')
            {
                if (last_flag != 1)
                {
                    write(2, "exit\n", 5);
                    write(2, "meowshell: exit: ", 18);
                    write(2, command[1], ft_strlen(command[1]));
                    write(2, " numeric argument required\n", 28);
                }
                return (255);
            }
            i++;
        }
        if (last_flag != 1)
            write(2, "exit\n", 6);
    }

    return (ft_atoi(command[1]));
}