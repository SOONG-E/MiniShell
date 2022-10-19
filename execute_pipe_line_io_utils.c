#include "minishell.h"

int	task_here_doc(t_symbol *symbol, int *fd)
{
	if (*fd != STDIN)
		close(*fd);
	if (read_here_doc(symbol->next->str) < 0)
		return (-1);
	*fd = open_file(".heredoc_tmp", T_IN_RID);
	if (*fd < 0)
		return (-1);
	return (1);
}
