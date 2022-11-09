#include "minishell.h"

int	fork_heredoc(char *limiter, int stdin_backup, char *heredoc_tmp)
{
	int pid;
	int	exitcode;

	pid = fork();
	if (pid == 0)
	{
		set_child_signal();
		read_here_doc(limiter, stdin_backup, heredoc_tmp);
	}
	else
	{
		block_signal();
		waitpid(pid, &exitcode, 0);
		if (WIFSIGNALED(exitcode) && WTERMSIG(exitcode) == 2)
		{
			g_info->flag = 1;
			set_signal();
			return (-1);
		}
	}
	set_signal();
	return (0);
}