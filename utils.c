#include "minishell.h"

void	prt_tree(t_node *node, int le, int ri)
{
	t_token	*token;

	printf("flag : %d, L : %d, R : %d :::", node->flag, le, ri);
	if (node->flag != 0)
	{
		token = node->token;
		while (token)
		{
			printf("%s ", token->str);
			token = token->next;
		}
	}
	printf("\n");
	if (node->left_child != NULL)
		prt_tree(node->left_child, le + 1, ri);
	if (node->right_child != NULL)
		prt_tree(node->right_child, le, ri + 1);
}
