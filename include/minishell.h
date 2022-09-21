#ifndef MINISHELL_H
# define MINISHELL_H

/* headers for allowed functions */
# include <stdio.h>				/* printf, strerror */
# include <fcntl.h>				/* open */
# include <unistd.h>			/* write, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot */
# include <stdlib.h>			/* malloc, free, exit, getenv */
# include <curses.h>			/* tgetent */
# include <signal.h>			/* signal, kill */
# include <dirent.h>			/* opendir, readdir, closedir*/
# include <termios.h>			/* tcsetattr, tcgetattr */
# include <sys/wait.h>			/* wait, wait3, wait4, waitpid */
# include <sys/stat.h>			/* stat, lstat, fstat */
# include <sys/ioctl.h>			/* ioctl */
# include <sys/errno.h>			/* errno */
# include "../libft/libft.h"
# include <readline/history.h>	/* add_history */
# include <readline/readline.h>	/* readline, rl_on_new_line, rl_replace_line, rl_redisplay */

//# include "symbols.h"
# include "./symbols.h"
/* struct definition */
typedef struct s_envlst
{
	char            *key;
    char            *value;
	struct s_envlst *next;
}	t_envlst;

typedef struct	s_token
{
	int		symbol;
	char 	*token;
}	t_token;

t_envlst	*g_envlst;

/*ft_lst_func.c*/
t_envlst	*ft_lst_new(char *key, char *value);
void		ft_lst_add_back(t_envlst *new);
void		printf_lst(void);
char		**parsing_cmd(char *str);
char		**ft_env_split(char *env);

void	is_space(char *str);
char	*double_quote(char *str);
char	*single_quote(char *str);
void	replace_white_space(char *str);

void	sub_env(char **temp);

void	allocat_error(void);

void	ft_split_free(char **str);

/// test
void	print_env_test(void);
void	test_print(char **temp);
void    printf_ls_test(void);
///
char	*ft_join(char **str);

char	*get_value_n(char *key, int n);
void    split_free(char **str);
#endif