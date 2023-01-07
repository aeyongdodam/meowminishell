
#include "../minishell.h"

void    builtin_export(t_envnode *envnode, char **command)
{
    t_envnode *tmp;
    tmp = envnode;
    while (tmp)
    {
        printf("declare -x ");
        printf("%s=",tmp->key);
        printf("\"%s\"\n", tmp->value);
        tmp = tmp->next;
    }
}