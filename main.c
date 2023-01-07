
#include "minishell.h"

int	g_exit_code;

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret;
	t_tree	*tree;
	t_envnode	*envnode;

	set_terminal();
	prt_meows();
	envnode = init_env(envp, tree);
	while(1)
	{
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		if (line)
		{
			tree = lexer(line, envnode);
			add_history(line);
			if (find_error(tree))
				continue;
			main_pipe(tree, envnode);
			free(line);
        }
		else
			prt_exit();
	}
	return (0);
}
