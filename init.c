
#include "minishell.h"

t_token  *init_token(void)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->prev = NULL;
    token->next = NULL;
    return (token);
}

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->token = init_token();
	node->left_child = NULL;
	node->right_child = NULL;
	return (node);
}

t_tree	*init_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	tree->root = init_node();
	return (tree);
}
