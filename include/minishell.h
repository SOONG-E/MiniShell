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

# include "./symbols.h"

# define SHELL "minishell"
# define C_BLUE "\033[34m"
# define C_NRML "\033[0m"

typedef	struct s_info 	t_info;
typedef struct s_envlst	t_envlst;
typedef struct s_symbol	t_symbol;
typedef struct s_token	t_token;
typedef struct s_child_info	t_child_info;

/* struct definition */
struct s_info
{
	t_envlst	*envlst;
	char		*home;
	char		*exit_code;
	int			oldpwd_flag;
};

struct s_envlst
{
	char		*key;
    char		*value;
	t_envlst	*next;
};

struct	s_symbol
{
	int			type;
	char		*str;
	t_symbol	*pre;
	t_symbol	*next;
};

struct	s_token
{
	t_symbol	*symbol;
	t_token		*left;
	t_token		*right;
	int			self;
};

/*
struct	s_child_info
{
	int			left_token;
	t_symbol	*left_symbol;
	int			right_token;
	t_symbol	*right_symbol;
	t_symbol	*curr_symbol;
};*/

//t_envlst	*g_envlst;
t_info		*g_info;

/*token_tree/ */
t_token		*and_or(t_symbol *symbol);
t_token		*brace_group(t_symbol *symbol);
t_token		*make_parse_tree(t_symbol *symbol);
t_token		*pipeline(t_symbol *symbol);
t_symbol	*skip_brace(t_symbol *symbol);

/*check_cmd.c*/
char	*get_cmd_path(char *cmd, char *path);
int		is_cmd(char	*str);

/* delete_quote.c */
void	delete_quote(t_symbol *symbol);

/*expand_env_double_quote.c*/
char	*expand_env_quote_case(char *str);

/*expand_env_utils.c*/
int		cut_temp(char **temp, char *str);
char	*cut_str(char **str);
int		count_pair(char *str);
char	*ft_join(char **str);

/*expand_env.c*/
t_symbol	*expand_env(t_symbol *symbol_lst);

/* expand_filename.c */
t_symbol	*expand_filename(t_symbol *symbol);

/*manage_env.c*/
void		parsing_env(char **env);
char		**ft_env_split(char *env);
char		*get_value_n(char *key, int n);

/*manage_envlst.c*/
t_envlst	*ft_envlst_new(char *key, char *value);
void		ft_envlst_add_back(t_envlst *new);
t_envlst	*get_envlst(char *key);
void		set_envlst(char *key, char *value);

/*manage_error.c*/
void	allocat_error(void);
int		error_msg(char *str);

/*manage_info.c*/
void	init_info(char **env);
void	set_exit_code(int code);

/*manage_mem.c*/
void    split_free(char **str);
void    free_symbol(t_symbol *symbols);
void    free_symbols(t_symbol *symbols);

/*manage_signal.c*/
void	sigint_handler(int signum);

/*manage_symbol.c*/
t_symbol	*ft_new_symbol(char	*str);
t_symbol	*make_symbol_lst(char **temp);
void		lst_symbol_add_back(t_symbol **head, t_symbol *new);
t_symbol	*lst_symbol_add_middle(t_symbol *symbol, t_symbol *new);

/*parse_line.c*/
char		**parse_line(char *str);

/*replace_space.c*/
void		is_space(char *str);
char		*double_quote(char *str);
char		*single_quote(char *str);
void		replace_white_space(char *str);

/*preprocess_line.c*/
char    **preprocess_line(char *str);
int		ft_skip_single_qoute(char *str);
int		ft_skip_double_qoute(char *str);

/* replace_wild_card.c */
void	replace_back_wild_card(char **str);
void	replace_wild_card(char *str);

/*symbolize.c*/
void	symbolizing(t_symbol *symbol_lst);
int		classify_op(char *str);

/*validate.c*/
int		validate(t_symbol *symbol_lst);
int		syntax_error_token(char *str);

/// test
//void	print_env_test(void);
//void	test_print(char **temp);
//void    printf_ls_test(void);
///

/* functions for built_in */
int			ft_cd(char *path);
void		ft_unset(char *rmvkey);
void		ft_pwd(void);
void		ft_export(char *key, char *value);
void		ft_echo(char *arg, int option);
void		ft_exit(int n);
void		ft_env(char *env);





/*------- seojin---------- */
char		*ft_get_value(char *str, int *idx);
char		*ft_get_env(char *key);
char		*ft_new_str(char *str, char *key, int *idx);
char		*ft_expand_env_in_double_quote(char *str);
void		ft_skip_quote(char *str, int *idx, int flag);
void		ft_backup_space_symbol(t_symbol *symbol);
void		ft_add_back_symbol(t_symbol **head, t_symbol *new);
int			ft_is_alnum(char c);
t_symbol	*ft_expand_env(t_symbol *symbol);
t_symbol	*ft_update_symbol(t_symbol *symbol, t_symbol *new);
t_symbol	*ft_new_symbol(char *str);
t_symbol	*ft_get_last_symbol(t_symbol *symbol);
t_symbol	*ft_expand_env_out_quote(char *str);

#endif
