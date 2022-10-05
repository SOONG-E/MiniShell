#include "./include/minishell.h"

void	sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ignore_signal(void)
{

}