#include "./include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**cmd;

    (void)av;
	if (ac != 1)
		return (0);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, sigint_handler);

	// struct termios	ori_term;
	// struct termios	new_term;

	// tcgetattr(STDIN_FILENO, &ori_term);
	// tcgetattr(STDIN_FILENO, &new_term);
	// new_term.c_lflag &= ~ICANON;
	// new_term.c_lflag &= ~ECHO;
	// tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	init_info(env);
	while (1)
	{
		str = readline(C_BLUE"minishell$ "C_BLCK);
		if (!strcmp(str, "exit"))
			exit(0);
		if (!ft_strlen(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		cmd = parsing_line(str);
		//system("leaks minishell");
	}
	return (0);
}
