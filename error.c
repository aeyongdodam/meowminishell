
#include "minishell.h"

int	error_pipe(t_tree *tree)
{
	t_node	*node;
	
	node = tree->root;
	while (node->right_child)
		node = node->right_child;
	if (node->token->flag == PIPE)
	{
		if (ft_strncmp(node->token->str, "||", 3) == 0)
		{
			return (1);
		}
		if (node->left_child == NULL)
			write(1, "minishell: syntax error near unexpected token '|'\n", 51);
		return (1);
	}
	return (0);
}

int	error_redi(t_node *node)
{
	t_token	*token;

	if (node->token->flag == WORD || node->token->flag == REDI)
	{
		token = node->token;
		while (token)
		{
			if (token->flag == REDI && token->next == NULL)
			{
				write(1, "minishell: syntax error near unexpected token `newline'\n", 56);
				return (1);
			}
			token = token->next;
		}
	}
	if (node->left_child != NULL)
		return (error_redi(node->left_child));
	if (node->right_child != NULL)
		return (error_redi(node->right_child));
	return (0);
}

int	find_error(t_tree *tree)
{
	t_node	*node;

	node = tree->root;
	if (error_pipe(tree))
		return (1);
	if (error_redi(tree->root))
		return (1);
	return (0);
}