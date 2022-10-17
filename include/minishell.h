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
# include "./structs.h"

# define SHELL	"minihell"
# define C_BLUE "\033[34m"
# define C_NRML "\033[0m"

t_info		*g_info;

/*token_tree*/ 
t_token		*and_or(t_symbol *symbol);
t_token		*brace_group(t_symbol *symbol);
t_token		*make_token(t_symbol *symbol);
t_token		*make_parse_tree(t_symbol *symbol);
t_token		*pipeline(t_symbol *symbol);
t_symbol	*skip_brace(t_symbol *symbol);

/*check_cmd.c*/
char		*get_cmd_path(char *cmd, char *path);
int			is_cmd(char	*str);

/* delete_quote.c */
void		delete_quote(t_symbol *symbol);

/*execute.c*/
void		execute_tree(t_token *tree);

/*expand_env_double_quote.c*/
char		*expand_env_quote_case(char *str);

/*expand_env_utils.c*/
int			cut_temp(char **temp, char *str);
char		*cut_str(char **str);
char		*ft_join(char **str);
int			count_pair(char *str);

/*expand_env.c*/
t_symbol	*expand_env(t_symbol *symbol_lst);

/* expand_filename.c */
void		expand_filename(t_symbol *symbol);

/*manage_env.c*/
int			get_env_len(char *env);
void		parse_env(char **env);
char		**ft_env_split(char *env);
char		*get_value_n(char *key, int n);

/*manage_envlst.c*/
t_envlst	*ft_envlst_new(char *key, char *value);
t_envlst	*get_envlst(char *key);
void		ft_envlst_add_back(t_envlst *new);
void		set_envlst(char *key, char *value);

/*manage_error.c*/
void		allocat_error(void);
int			error_msg(char *str);
void		execute_error(char *cmd);

/*manage_info.c*/
void		init_info(char **env);
void		set_exit_code(int code);

/*manage_mem.c*/
void		split_free(char **str);
void		free_symbol(t_symbol *symbols);
void		free_symbols(t_symbol *symbols);

/*manage_signal.c*/
void		set_child_signal(void);
void		block_signal(void);
void		set_signal(void);

/*manage_symbol.c*/
t_symbol	*ft_new_symbol(char	*str);
t_symbol	*make_symbol_lst(char **temp);
void		lst_symbol_add_back(t_symbol **head, t_symbol *new);
t_symbol	*lst_symbol_add_middle(t_symbol *symbol, t_symbol *new);

/*parse_line.c*/
t_token	*parse_line(char *str);

/*replace_space.c*/
void		is_space(char *str);
char		*double_quote(char *str);
char		*single_quote(char *str);
void		replace_white_space(char *str);

/*preprocess_line.c*/
char		**preprocess_line(char *str);
char		*replace_op(char *line);

/* replace_wild_card.c */
void		replace_back_wild_card(char **str);
void		replace_wild_card(char *str);

/*symbolize.c*/
void		symbolizing(t_symbol *symbol_lst);
int			classify_op(char *str);

/*validate.c*/
int			validate(t_symbol *symbol_lst);
int			syntax_error_token(char *str);

/* functions for built_in */
void		ft_cd(char **path, int pipe_cnt);
t_cd		*ft_init_cd_info(int pipe_cnt, char *arg);
void		ft_check_rv(t_cd *info);
void		ft_cd_home(int pipe_cnt);
void		ft_update_oldpwd(char *old_pwd);
void		ft_update_pwd(char *pwd);
void		ft_unset(char **arg, int pipe_cnt);
void		ft_pwd(char **arg, int pipe_cnt);
void		ft_export(char **arg, int pipe_cnt);
void		ft_pipe_export(char **arg);
void		ft_echo(char **arg, int pipe_cnt);
void		ft_exit(char **arg, int pipe_cnt);
void		ft_env(char **arg, int pipe_cnt);

/* execute_pipe_line.c */
void		execute_pipe_line(t_symbol *symbol);

/* execute_pipe_line_utils.c */
int			get_exitcode(int status);
void		close_all_pipefd(int *fd, int error_case);
int			get_pipe_cnt(t_symbol *symbol);
int			open_file(char *file, int redirection_type);
int			dup_in_redirection(t_symbol *symbol);
int			dup_out_redirection(t_symbol *symbol);

/* make_env.c */
char		**make_env(void);

/*------- seojin---------- */
char		*get_value(char *str, int *idx);
char		*get_env(char *key);
char		*new_str(char *str, char *key, int *idx);
void		skip_quote(char *str, int *idx, int flag);
void		backup_space_symbol(t_symbol *symbol);
void		add_back_symbol(t_symbol **head, t_symbol *new);
t_symbol	*expand_env(t_symbol *symbol);
t_symbol	*update_symbol(t_symbol *symbol, t_symbol *new);
t_symbol	*new_symbol(char *str);
t_symbol	*get_last_symbol(t_symbol *symbol);

#endif
