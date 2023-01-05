
#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		ret;
	t_tree	*tree;
	t_envnode	*envnode;

	set_terminal();
	envnode = init_env(envp);
	while(1)
	{
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		
		if (line)
        {
			tree = lexer(line);
			main_pipe(tree, envp);
			add_history(line);
			free(line);
        }
        else
        {
            // printf("ctrl + d\n");
			exit(0);
        }
	}
	return (0);
}
