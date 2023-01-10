
#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			ret;
	t_tree		*tree;
	t_envnode	*envnode;

	set_terminal();
	prt_meows();
	envnode = init_env(envp, tree);
	while (1)
	{
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		if (!line)
			prt_exit();
		tree = lexer(line, envnode);
		if (tree->root->left_child != NULL || tree->root->right_child != NULL)
			add_history(line);
		if (find_error(tree))
			continue ;
		create_heredoc_file(tree);
		main_pipe(tree, envnode, envp);
		// delete_heredoc_file(tree);
		free(line);
	}
	return (0);
}
