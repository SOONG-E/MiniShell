#include "../include/minishell.h"

t_token	*brace_group(t_symbol *symbol)
{
	t_symbol *temp;

	symbol = symbol->next;
	printf("symbol = %s\n", symbol->str);
	//free_symbol(symbol->pre);
	symbol->pre = NULL;
	temp = get_last_symbol(symbol);
	printf("1111 %d %s\n", temp->type, temp->str);
	if (temp->pre)
		temp->pre->next = NULL;
	temp = get_last_symbol(symbol);
	printf("2222 %d %s\n", temp->type, temp->str);
	///
	t_symbol *save;
	save = symbol;
	printf("brace : ");
	while (save)
	{
		printf("%s ", save->str);
		save = save->next;
	}
	printf("\nend\n");
	
	//free_symbol(temp);
	return (and_or(symbol));
}
