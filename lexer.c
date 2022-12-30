
#include "minishell.h"

char	*str_one_join(char *s1, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i+1] = 0;
	free(s1);
	return (str);
}

char	*re_str(char *str)
{
	free(str);
	str = malloc(1);
	str[0] = 0;
	return (str);
}

void	save_token(t_node *node, char *str, int flag)
{
	t_token	*token;

	if (node->left_child == NULL) //처음 토큰
	{
		node->left_child = init_node();
		node->left_child->flag = flag;
		token = node->left_child->token;
		token->str = ft_strdup(str);
	}
	else
	{
		token = node->left_child->token;
		while (token->next)
			token = token->next;
		token->next = init_token();
		token->next->prev = token;
		token->next->str = ft_strdup(str);
	}
}

void	prt_tree(t_node *node, int le, int ri)
{
	t_token	*token;

	printf("flag : %d, L : %d, R : %d :::",node->flag,le,ri);
	if (node->flag != 0)
	{
		token = node->token;
		while (token)
		{
			printf("%s ",token->str);
			token = token->next;
		}
	}
	printf("\n");
	if (node->left_child != NULL)
		prt_tree(node->left_child,le+1,ri);
	if (node->right_child != NULL)
		prt_tree(node->right_child,le,ri+1);
}