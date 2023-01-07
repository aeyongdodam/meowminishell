
#include "../minishell.h"

void builtin_env(t_envnode *envnode)
{
    t_envnode *tmp;
    tmp = envnode;
    while (tmp)
    {
        printf("%s", tmp->key);
        printf("=");
        printf("%s\n", tmp->value);
        tmp = tmp->next;
    }
}