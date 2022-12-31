
#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		return ;
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
	}
}

void	set_signal_handler(int flag)
{
	if (!flag)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	else
	{
		signal(SIGQUIT, signal_handler2);
		signal(SIGINT, signal_handler);
	}
}

void	set_terminal(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}