#include "./include/minishell.h"

// void	test_print(char **temp)
// {
// 	int i = 0;
// 	while (temp[i])
// 	{
// 		printf("%s\n", temp[i]);
// 		i++;
// 	}
// }

// void    printf_ls_test(void)
// {
//     t_envlst	*temp;

// 	temp = g_envlst;
// 	while (temp)
// 	{
// 		printf("KEY: %s\nVALUE: %s\n", temp->key, temp->value);
// 		temp = temp->next;
// 	}
// }

// void	print_env_test()
// {
// 	t_envlst	*temp;

// 	temp = g_envlst;
// 	while (temp)
// 	{
// 		printf("key = %s || value = %s\n", temp->key, temp->value);
// 		temp = temp->next;
// 	}
// }

// int main()
// {
// 	char	buf[100];

// 	getcwd(buf, 100);
// 	printf("%s\n", buf);
// 	return (0);
// }