/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwon <mkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:21:07 by mkwon             #+#    #+#             */
/*   Updated: 2023/01/12 23:21:11 by mkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_code;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		write(2, "^C\n", 3);
	}
	else if (sig == SIGQUIT)
	{
		g_exit_code = 131;
		write(2, "^\\Quit: 3\n", 10);
	}
}

void	set_signal_handler(int flag)
{
	if (flag == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	else if (flag == 1)
	{
		signal(SIGQUIT, signal_handler2);
		signal(SIGINT, signal_handler2);
	}
	else if (flag == 3)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

void	set_terminal(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}
