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

/* struct definition */
typedef struct s_envlst
{
	char            *key;
    char            *value;
	struct s_envlst *next;
}	t_envlst;

t_envlst	*g_envlst;

/*ft_lst_func.c*/
t_envlst	*ft_lst_new(char *key, char *value);
void		ft_lst_add_back(t_envlst *new);
void		printf_lst(void);

#endif



















#define LBRACE	"("
#define RBRACE	")"
#define AND_IF	"&&"
#define OR_IF 	"||"
#define PIPE	"|"
