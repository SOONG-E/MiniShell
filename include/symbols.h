#ifndef	SYMBOLS_H
# define SYMBOLS_H

# define T_CMD			0
# define T_FILEPATH		1
# define T_OPTION		2
# define T_ARG			3
# define T_PIPE			4
# define T_AND_IF		5
# define T_OR_IF		6
# define T_LBRACE		7
# define T_RBRACE		8
# define T_IN_RID		9
# define T_OUT_RID		10
# define T_IN_HEREDOC	11
# define T_OUT_HEREDOC	12

# define OP_PIPE		-40
# define OP_AND_IF		-50
# define OP_OR_IF		-60
# define OP_LBRACE		-70
# define OP_RBRACE		-80
# define OP_IN_HEREDOC  -90
# define OP_OUT_HEREDOC	-100
# define OP_IN_RID		-110
# define OP_OUT_RID		-120

# define Q_SINGLE		'\''
# define Q_DOUBLE		'\"'

#endif