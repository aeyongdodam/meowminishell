
#include "../minishell.h"

void    builtin_pwd(char **command)
{
    char buf[255];
    printf("%s\n",getcwd(buf, 255));
}