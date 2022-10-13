NAME		=	minishell

CC			= 	cc -g
CFLAGS		=	-Wall -Werror -Wextra 
LDFLAGS		=	-L/$(HOME)/.brew/opt/readline/lib
LDLIBS		=	-lreadline
CPPFLAGS	=	-I/$(HOME)/.brew/opt/readline/include
CPPFLAGS	+=	-I./include

OUTDIR = out/

# INCLUDE		=	include
# LIBFT		=	libft
LIBFT		=	./libft/libft.a
LIBMINI		=	libmini.a
SRCS		= 	main.c						\
				parse_line.c				\
				replace_space.c				\
				replace_op.c				\
				replace_op_utils.c			\
				expand_env.c				\
				expand_env_utils.c			\
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
				delete_quote.c				\
				./token_tree/and_or.c		\
				./token_tree/brace_group.c	\
				./token_tree/make_parse_tree.c\
				./token_tree/pipeline.c		\
				./token_tree/utils.c		\
				./test/test_tree.c
#				replace_wild_card.c			\
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

# $(NAME) : $(OBJS)
# 			make -C $(LIBFT)
# 			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT) -lft $(LDFLAGS) $(CPPFLAGS) -I $(INCLUDE)
# 			make clean
$(NAME) : $(LIBFT) $(LIBMINI)
	$(CC) $(LIBFT) $(LIBMINI) main.c -o $@ $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)
#	make clean
#main.c수정했는데 재컴파일이 안돼서 수정했습니다

$(LIBFT) :
	cd libft; make

$(LIBMINI) : $(OBJS)
	ar rc $@ $^

clean	:
			rm -rf $(OBJS)
			cd libft; make clean

fclean	: clean
			rm -rf $(NAME) $(LIBMINI)

re		:
			make fclean
			make all

.PHONY	: all clean fclean re
