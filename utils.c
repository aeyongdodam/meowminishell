
#include "minishell.h"

int	input_exit(t_tree *tree)
{
	if (ft_strncmp(tree->root->left_child->token->str, "exit", 5) == 0)
		return (1);
	return (0);
}

void	prt_exit(void)
{
	write(2, "exit\n", 5);
	exit(0);
}

void	prt_meows(void)
{
	int		fd;
	int		n;
	char 	*buf;

	fd = open("meow.txt", O_RDONLY);
	buf = ft_calloc(2, 1);
	while (read(fd, buf, 1) > 0)
	{
		printf("%s", buf);
	}
	printf("\n");
	free(buf);
}

void	prt_tree(t_node *node, int le, int ri)
{
	t_token	*token;

	printf("L : %d, R : %d :::", le, ri);
	if (node->token->flag != 0)
	{
		token = node->token;
		while (token)
		{
			printf("flag : %d, str : %s / ", token->flag, token->str);
			token = token->next;
		}
	}
	printf("\n");
	if (node->left_child != NULL)
		prt_tree(node->left_child, le + 1, ri);
	if (node->right_child != NULL)
		prt_tree(node->right_child, le, ri + 1);
}
