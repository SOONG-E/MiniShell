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

typedef struct	s_symbol
{
	int		type;
	char	*str;
}	t_symbol;

typedef struct	s_token
{
	struct s_symbol	symbol;
	struct s_token	*left;
	struct s_token	*right;
	//struct s_token	*parent;
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

t_symbol	*symbolizing(char **temp);

//substitution_env.c
void	sub_env(char **temp);

//manage_error.c
void	allocat_error(void);

//manage_split.c
void	ft_split_free(char **str);

/// test
//void	print_env_test(void);
//void	test_print(char **temp);
//void    printf_ls_test(void);
///
char	*ft_join(char **str);

char	*get_value_n(char *key, int n);
void    split_free(char **str);
void    free_symbol(t_symbol *symbols);

/* functions for built_in */
void	ft_cd(char *path);
void	ft_unset(char *rmvkey);
void	ft_pwd(void);
void	ft_export(char *key, char *value);
void	ft_echo(char *arg, int option);
void	ft_exit(int n);
void	ft_env(char *env);

//preprocess_str.c
char    *preprocess_str(char *str);

//substitution_env_utils.c
int		cut_temp(char **temp, char *str);
char	*cut_str(char **str);
int		count_pair(char *str);
char	*ft_join(char **str);

//check_cmd.c
char	*get_cmd_path(char *cmd, char *path);
int		is_cmd(char	*str);

//manage_env
void	parsing_env(char **env);

#endif
