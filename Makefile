NAME		=	minishell

CC			= 	cc -g
CFLAGS		=	-Wall -Werror -Wextra
# CFLAGS		=

INCLUDE		=	include
LIBFT		=	libft

SRCS		= 	main.c						\
				parsing_line.c				\
				replace_space.c				\
				expand_env.c				\
				expand_env_utils.c			\
				expand_env_double_quote.c	\
				manage_symbol.c				\
				manage_envlst.c				\
				manage_error.c				\
				manage_env.c				\
				manage_mem.c				\
				symbolize.c					\
				preprocess_line.c			\
				check_cmd.c					\
				validate.c					\
				manage_info.c	
# ./built_in/ft_cd.c			\
# ./built_in/ft_echo.c		\
# ./built_in/ft_env.c			\
# ./built_in/ft_exit.c		\
# ./built_in/ft_export.c		\
# ./built_in/ft_pwd.c			\
# ./built_in/ft_unset.c

OBJS		=	$(SRCS:%.c=%.o)

all		: $(NAME)

$(NAME) : $(OBJS)
			make -C $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT) -lft -Lvendor/readline/lib -lreadline -I $(INCLUDE)
			make clean  

clean	:
			rm -rf $(OBJS)
			make clean -C $(LIBFT)

fclean	: clean
			rm -rf $(NAME)
			$(RM) $(LIBFT)/libft.a
	
re		:
			make fclean
			make all

PHONY : all clean fclean re
