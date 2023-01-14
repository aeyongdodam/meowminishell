/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohlee <sohlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:10:50 by sohlee            #+#    #+#             */
/*   Updated: 2023/01/15 01:48:50 by sohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	builtin1(t_pipe *pi, t_envnode *envnode)
{
	if (!pi->command[0] && pi->index > 0)
		exit (0);
	else if (ft_strncmp(pi->command[0], "echo", 5) == 0)
	{
		builtin_echo(pi->command);
		exit (0);
	}
	else if (ft_strncmp(pi->command[0], "cd", 3) == 0)
		exit (builtin_cd(pi->command, envnode, 0));
	else if (ft_strncmp(pi->command[0], "pwd", 4) == 0)
	{
		builtin_pwd();
		exit (0);
	}
	else if (ft_strncmp(pi->command[0], "env", 4) == 0)
	{
		exit(builtin_env(envnode, pi->command, 0));
		exit (0);
	}
	else if (ft_strncmp(pi->command[0], "export", 7) == 0)
		exit (builtin_export(envnode, pi->command, 0));
}

void	builtin2(t_pipe *pi, t_envnode *envnode)
{
	if (ft_strncmp(pi->command[0], "unset", 6) == 0)
	{
		builtin_unset(envnode, pi->command);
		exit (0);
	}
	else if (ft_strncmp(pi->command[0], "exit", 5) == 0)
		g_exit_code = (builtin_exit(pi->command, 0));
}

int	builtin_strncmp(t_tree *tree, t_node *tr)
{
	if (tree->pipe_cnt == 0 && \
	((ft_strncmp(tr->left_child->token->str, "cd", 3) == 0 || \
	ft_strncmp(tr->left_child->token->str, "export", 7) == 0) || \
	(ft_strncmp(tr->left_child->token->str, "unset", 6) == 0 && \
	!tr->right_child) || \
	(ft_strncmp(tr->left_child->token->str, "exit", 5) == 0 \
	&& !tr->right_child)))
		return (1);
	return (0);
}

void	handle_builtin_parent(t_tree *tree, t_node *tr, \
t_envnode *envnode, t_pipe *pi)
{
	tr = tree->root;
	if (builtin_strncmp(tree, tr))
	{
		if (check_redi(tr))
			pi->command = get_redi_command(tr);
		else
			pi->command = get_command(tr);
		if (ft_strncmp(tr->left_child->token->str, "cd", 3) == 0)
			g_exit_code = builtin_cd(pi->command, envnode, 1);
		else if (ft_strncmp(tr->left_child->token->str, "export", 7) == 0)
			g_exit_code = builtin_export(envnode, pi->command, 1);
		else if (ft_strncmp(tr->left_child->token->str, "exit", 5) == 0)
		{
			g_exit_code = builtin_exit(pi->command, 1);
		}
		else
			g_exit_code = builtin_unset(envnode, pi->command);
		free_split(pi->command);
	}
}
