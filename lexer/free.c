
#include "../minishell.h"

void	free_token(t_token **token)
{
	t_token *temp;

	while (*token)
	{
		temp = *token;
		*token = (*token)->next;
		free (temp->str);
		free(temp);
	}
}

void	free_node(t_node **node)
{
	if ((*node)->left_child != NULL)
		free_node(&((*node)->left_child));
	if ((*node)->right_child != NULL)
		free_node(&((*node)->right_child));
	free_token(&((*node)->token));
	free(*node);
}

void	all_free(t_tree **tree, char *line)
{
	free(line);
	free_node(&((*tree)->root));
	free(*tree);
}
