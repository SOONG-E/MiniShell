#include "minishell.h"

int	count_after_rid(t_symbol *symbol)
{
	int	cnt;

	cnt = 0;
	symbol = symbol->next->next;
	while (symbol && symbol->type != T_CMD)
	{
		if (symbol->type == T_IN_HEREDOC || symbol->type == T_IN_RID)
			cnt++;
		symbol = symbol->next->next;
	}
	return (cnt);
}

int	task_here_doc(t_symbol *symbol, int *fd)
{
	if (read_here_doc(symbol->next->str) < 0)
		return (-1);
	if (count_after_rid(symbol))
		return (0);
	else
	{
		*fd = open_file(".heredoc_tmp", T_IN_RID);
		if (*fd < 0)
			return (-1);
		return (DID_IN_RID);
	}
}


