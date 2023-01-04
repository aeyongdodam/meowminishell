
#include "minishell.h"

void	save_token(t_node *node, char *str, int flag)
{
	t_token	*token;

	if (node->left_child == NULL)
	{
		node->left_child = init_node();
		token = node->left_child->token;
		token->str = ft_strdup(str);
		token->flag = flag;
	}
	else
	{
		token = node->left_child->token;
		while (token->next)
			token = token->next;
		token->next = init_token();
		token->next->prev = token;
		token->next->str = ft_strdup(str);
		token->next->flag = flag;
	}
}

t_node	*pipe_token(t_node *node, char *str, int *space, int *pipe)
{
	if (*pipe == 1)
	{
		exit(1);
	}
	if (space == 0 && str[0] != 0)
	{
		save_token(node, str, WORD);
		str = re_str(str);
	}
	node->right_child = init_node();
	node->right_child->token->flag = PIPE;
	node->right_child->token->str = ft_strdup("|");
	node = node->right_child;
	*space = 0;
	*pipe = 1;
	return (node);
}

int	redi_token(t_node *node, char *line, char *str, int *space)
{
	if (*space == 0 && str[0] != 0)
	{
		save_token(node, str, WORD);
		str = re_str(str);
	}
	if (*line == '<' && *(line + 1) == '<')
	{
		save_token(node, "<<", HERE);
		return (1);
	}
	else if (*line == '>' && *(line + 1) == '>')
	{
		save_token(node, ">>", REDI);
		return (1);
	}
	else if (*line == '<')
		save_token(node, "<", REDI);
	else if (*line == '>')
		save_token(node, ">", REDI);
	return (0);
}

t_tree	*lexer(char	*line)
{
	t_tree	*tree;
	t_node	*node;
	char	*str;
	int		space;
	int		pipe;

	str = malloc(1);
	str[0] = 0;
	tree = init_tree();
	node = tree->root;
	node->token->flag = 0;
	space = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			if (space == 0 && str[0] != 0) //연속 space 제거
			{
				save_token(node, str, WORD);
				str = re_str(str);
				space = 1;
				pipe = 0;
			}
		}
		else if (get_type(line) == PIPE)
			node = pipe_token(node, str, &space, &pipe);
		else if (get_type(line) == REDI || get_type(line) == HERE)
		{
			if (redi_token(node, line, str, &space))
			line++;
		}
		else
		{
			str = str_one_join(str, line[0]);
			space = 0;
			pipe = 0;
		}
		line++;
	}
	if (str[0] != 0) //마지막 문자열
	{
		save_token(node, str, WORD);
		str = re_str(str);
	}
	// prt_tree(tree->root, 0, 0);
	free(str);
	return (tree);
}
