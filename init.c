
#include "minishell.h"

t_token	*init_token(void)
{
	t_token	*token;

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
	tree->pipe_cnt = 0;
	tree->ridi_cnt = 0;
	tree->heredoc_cnt = 0;
	tree->space = 0;
	tree->pipe = 0;
	tree->double_quote = 0;
	tree->single_quote = 0;
	return (tree);
}

t_envnode	*init_envnode(t_envnode	**head, char	*str)
{
	t_envnode	*node;
	t_envnode	*tempnode;

	node = malloc(sizeof(t_envnode));
	node->prev = 0;
	node->next = 0;
	node->key = ft_strdup(str);
	if (*head == NULL)
		*head = node;
	else
	{
		tempnode = *head;
		while (tempnode->next)
			tempnode = tempnode->next;
		tempnode->next = node;
		node->prev = tempnode;
	}
	return (node);
}

t_envnode	*init_env(char **envp)
{
	t_envnode	*head;
	t_envnode	*node;
	char		*str;

	head = NULL;
	str = malloc(1);
	str[0] = 0;
	while (*envp != 0)
	{
		while (**envp != 0)
		{
			if (**envp == '=')
			{
				node = init_envnode(&head, str);
				str = re_str(str);
			}
			else
				str = str_one_join(str, *envp[0]);
			(*envp)++;
		}
		node->value = ft_strdup(str);
		str = re_str(str);
		envp++;
	}
	return (head);
}
