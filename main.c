/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:02:20 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/15 01:02:26 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_tree		*tree;
	t_envnode	*envnode;

	set_terminal(argc, argv, &tree);
	envnode = init_env(envp, tree, -1, -1);
	set_oldpwd(&envnode);
	while (1)
	{
		set_signal_handler(0);
		line = readline("Minishell> ");
		if (!line)
			prt_exit();
		tree = lexer(line, envnode);
		if (!(find_error(tree, line)))
		{
			create_heredoc_file(tree);
			main_pipe(tree, envnode, envp);
			delete_heredoc_file(tree);
		}
		all_free(&tree, line);
	}
	return (0);
}
