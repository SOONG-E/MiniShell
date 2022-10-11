NAME		=	minishell

CC			= 	cc -g
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-L/$(HOME)/.brew/opt/readline/lib -lreadline
CPPFLAGS	=	-I/$(HOME)/.brew/opt/readline/include

OUTDIR = out/

INCLUDE		=	include
LIBFT		=	libft

SRCS		= 	main.c						\
				parse_line.c				\
				replace_space.c				\
				expand_env.c				\
				expand_env_utils.c			\
				expand_env_double_quote.c	\
				expand_env_double_quote_utils.c	\
				manage_symbol.c				\
				manage_envlst.c				\
				manage_error.c				\
				manage_env.c				\
				manage_mem.c				\
				manage_signal.c				\
				symbolize.c					\
				preprocess_line.c			\
				check_cmd.c					\
				validate.c					\
				manage_info.c				\
				expand_filename.c			\
				delete_quote.c
# ./built_in/ft_cd.c			\
# ./built_in/ft_echo.c		\
# ./built_in/ft_env.c			\
# ./built_in/ft_exit.c		\
# ./built_in/ft_export.c		\
# ./built_in/ft_pwd.c			\
# ./built_in/ft_unset.c

#OBJS		=	$(SRCS:%.c=$(OUTDIR)%.o)
OBJS		=	$(SRCS:%.c=%.o)

all		: $(NAME)

#$(OBJS): $(OUTDIR)%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
			make -C $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT) -lft $(LDFLAGS) $(CPPFLAGS) -I $(INCLUDE)
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
