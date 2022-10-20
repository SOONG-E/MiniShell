#include "minishell.h"

void	init_shell(char **env)
{
	// int		shell_img;
	// char	img;

	// shell_img = open(".daengdaeng.txt", O_RDONLY);
	// if (shell_img < 0)
	// 	exit(1);
	// while (read(shell_img, &img, 1) > 0)
	// {
	// 	write(1, &img, 1);
	// 	usleep(600);
	// }
	// close(shell_img);
	init_info(env);
}

void	execute(char *str)
{
	t_token	*cmd;

	cmd = parse_line(str);
	execute_tree(cmd);
	free_tree(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	if (ac != 1 && av)
		return (0);
	init_shell(env);
	while (1)
	{
		set_signal();
		str = readline(C_BLUE "minihell$ " C_NRML);
		if (!str)
			exit(0);
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		execute(str);
	}
	return (0);
}
