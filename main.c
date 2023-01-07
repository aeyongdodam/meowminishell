
#include "minishell.h"

int	g_exit_code;

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret;
	t_tree	*tree;
	t_envnode	*envnode;

	set_terminal();
	envnode = init_env(envp, tree);
	while(1)
	{
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		if (line)
        {
			tree = lexer(line, envnode);
			main_pipe(tree, envnode);
			add_history(line);
			// set_signal_handler(1);
			free(line);
        }
        else
        {
            write(2, "exit\n", 5);
			exit(0);
			//free함수 추가
        }
	}
	return (0);
}
