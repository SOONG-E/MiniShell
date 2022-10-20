#include "minishell.h"

int	execute_single_command(t_symbol *symbol, int pipe_cnt)
{
	char	**cmd_arr;
	int		fd_back_up;

	if (!pipe_cnt)
	{
		cmd_arr = make_cmd_arr(symbol);
		if (is_built_in(cmd_arr))
		{
			fd_back_up = dup(STDOUT);
			if (dup_redirection(symbol) < 0)
			{
				split_free(cmd_arr);
				dup2(fd_back_up, STDOUT);
				close(fd_back_up);
				return (1);
			}
			execute_built_in(cmd_arr, pipe_cnt);
			split_free(cmd_arr);
			dup2(fd_back_up, STDOUT);
			close(fd_back_up);
			return (1);
		}
		if (cmd_arr)
			split_free(cmd_arr);
	}
	return (0);
}