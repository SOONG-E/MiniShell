#ifndef STRUCTS_H
# define STRUCTS_H

struct s_info;
struct s_envlst;
struct s_symbol;
struct s_token;
struct s_child_info;

typedef struct s_info
{
	struct s_envlst	*envlst;
	char			*home;
	char			*exit_code;
	int				oldpwd_flag;
}	t_info;

typedef struct s_envlst
{
	char			*key;
    char			*value;
	struct s_envlst	*next;
}	t_envlst;

typedef struct	s_symbol
{
	int				type;
	char			*str;
	struct s_symbol	*pre;
	struct s_symbol	*next;
}	t_symbol;

typedef struct	s_token
{
	struct s_symbol	*symbol;
	struct s_token	*left;
	struct s_token	*right;
	int				self;
}	t_token;

#endif
