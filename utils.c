
#include "minishell.h"

extern int	g_exit_code;

int	input_exit(t_tree *tree)
{
	t_token	*token;

	token = tree->root->left_child->token;
	if (ft_strncmp(token->str, "exit", 5) == 0)
	{
		if (token->next != NULL)
			g_exit_code = ft_atoi(token->next->str);
		return (1);
	}
	return (0);
}

void	prt_exit(void)
{
	write(2, "exit\n", 5);
	if (g_exit_code > 255)
		g_exit_code = g_exit_code - 256;
	if (g_exit_code < 0)
		g_exit_code += 256;
	exit(g_exit_code);
}

void	prt_meows(void)
{
	int		fd;
	int		n;
	char	*buf;

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
