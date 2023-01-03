
#include "minishell.h"

int main(int argc, char **argv, char *envp[])
{
	char	*line;
	int		ret;
	t_tree	*tree;

	set_terminal();
	while(1)
	{
		// printf("new\n");
		set_signal_handler(0);
		line = readline("\033[34mMinishell>\033[0m ");
		
		if (line)
        {
            //printf("output> %s\n", line);
			tree = lexer(line);
			main_pipe(tree, envp);
			// printf("*");
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
