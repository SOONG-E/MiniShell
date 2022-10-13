.DEFAULT_GOAL = all

NAME		=	minishell

RM			=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP -g
CPPFLAGS	=	-I./include -I$(HOME)/.brew/opt/readline/include
LDFLAGS		=	-L./libft -L$(HOME)/.brew/opt/readline/lib
LDLIBS		=	-lft -lreadline

OUTDIR		=	out/

LIBFT		=	./libft/libft.a

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
				token_tree/and_or.c		\
				token_tree/brace_group.c	\
				token_tree/make_parse_tree.c\
				token_tree/pipeline.c		\
				token_tree/utils.c		\
				test/test_tree.c
#				replace_wild_card.c			\
# ./built_in/ft_cd.c			\
# ./built_in/ft_echo.c		\
# ./built_in/ft_env.c			\
# ./built_in/ft_exit.c		\
# ./built_in/ft_export.c		\
# ./built_in/ft_pwd.c			\
# ./built_in/ft_unset.c

OBJS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.o))
DEPS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.d))
-include $(DEPS)

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	
all		:
	$(MAKE) -C $(dir $(LIBFT))
	$(MAKE) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJS) : $(LIBFT)

$(LIBFT) : 
	@$(MAKE) -C $(dir $(LIBFT))

clean	:
	@$(RM) $(OUTDIR)
	@$(MAKE) -C libft clean

fclean	: clean
	@$(RM) $(NAME) $(LIBFT)

re		: fclean
	$(MAKE) all

.PHONY	: all clean fclean re $(dir $(LIBFT))