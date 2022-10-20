#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	set_exit_code(1);
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_child_signal(void)
{
	rl_catch_signals = 1;
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(errno);
}

void	block_signal(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(errno);
}

void	set_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(errno);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(errno);
}
