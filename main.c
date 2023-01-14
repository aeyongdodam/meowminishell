
#include "minishell.h"

int	g_exit_code;

void	prt_tree(t_node *node, int le, int ri)
{
	t_token	*token;

	printf("L : %d, R : %d :::", le, ri);
	if (node->token->flag != 0)
	{
		token = node->token;
		while (token)
		{
			printf("flag : '%d', str : '%s' / ", token->flag, token->str);
			token = token->next;
		}
	}
	printf("\n");
	if (node->left_child != NULL)
		prt_tree(node->left_child, le + 1, ri);
	if (node->right_child != NULL)
		prt_tree(node->right_child, le, ri + 1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			ret;
	t_tree		*tree;
	t_envnode	*envnode;

	set_terminal();
	prt_meows();
	envnode = init_env(envp, tree);
	set_oldpwd(&envnode);
	while (1)
	{
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		if (!line)
			prt_exit();
		tree = lexer(line, envnode);
		// prt_tree(tree->root, 0, 0);
		if (find_error(tree, line))
			continue ;
		create_heredoc_file(tree);
		main_pipe(tree, envnode, envp);
		delete_heredoc_file(tree);
		all_free(&tree, line);
	}
	return (0);
}