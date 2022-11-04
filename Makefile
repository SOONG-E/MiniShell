.DEFAULT_GOAL = all

NAME		=	minishell
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP
CPPFLAGS	=	-I./$(DIR)include -I$(HOME)/.brew/opt/readline/include
LDFLAGS		=	-L./libft -L$(HOME)/.brew/opt/readline/lib
LDLIBS		=	-lft -lreadline
RM			=	rm -rf

OUTDIR		=	out/

DIR = mandatory/
TAIL = 
ifdef bonus
	DIR = bonus/
	TAIL = _bonus
endif

LIBFT		=	./libft/libft.a

SRCS		= 	$(DIR)main$(TAIL).c							\
				$(DIR)parse_line$(TAIL).c					\
				$(DIR)replace_space$(TAIL).c					\
				$(DIR)replace_op$(TAIL).c					\
				$(DIR)expand_env$(TAIL).c					\
				$(DIR)expand_env_utils$(TAIL).c				\
				$(DIR)manage_symbol$(TAIL).c					\
				$(DIR)manage_envlst$(TAIL).c					\
				$(DIR)manage_error$(TAIL).c					\
				$(DIR)manage_env$(TAIL).c					\
				$(DIR)manage_mem$(TAIL).c					\
				$(DIR)manage_signal$(TAIL).c					\
				$(DIR)symbolize$(TAIL).c						\
				$(DIR)preprocess_line$(TAIL).c				\
				$(DIR)check_cmd$(TAIL).c						\
				$(DIR)validate$(TAIL).c						\
				$(DIR)validate_utils$(TAIL).c				\
				$(DIR)manage_info$(TAIL).c					\
				$(DIR)expand_filename$(TAIL).c				\
				$(DIR)delete_quote$(TAIL).c					\
				$(DIR)execute$(TAIL).c						\
				$(DIR)token_tree/and_or$(TAIL).c				\
				$(DIR)token_tree/brace_group$(TAIL).c		\
				$(DIR)token_tree/make_parse_tree$(TAIL).c	\
				$(DIR)token_tree/pipeline$(TAIL).c			\
				$(DIR)token_tree/utils$(TAIL).c				\
				$(DIR)execute_pipe_line$(TAIL).c				\
				$(DIR)execute_pipe_line_utils$(TAIL).c		\
				$(DIR)execute_pipe_line_io$(TAIL).c			\
				$(DIR)execute_pipe_line_io_utils$(TAIL).c	\
				$(DIR)execute_single_commend$(TAIL).c		\
				$(DIR)replace_wild_card$(TAIL).c				\
				$(DIR)make_env$(TAIL).c						\
				$(DIR)built_in/ft_cd$(TAIL).c				\
				$(DIR)built_in/ft_cd_utils$(TAIL).c			\
				$(DIR)built_in/ft_echo$(TAIL).c				\
				$(DIR)built_in/ft_env$(TAIL).c				\
				$(DIR)built_in/ft_exit$(TAIL).c				\
				$(DIR)built_in/ft_export$(TAIL).c			\
				$(DIR)built_in/ft_pwd$(TAIL).c				\
				$(DIR)built_in/ft_unset$(TAIL).c				\
				$(DIR)built_in/ft_pipe_export$(TAIL).c	

OBJS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.o))
DEPS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.d))
-include $(DEPS)

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

bonus : 
	$(MAKE) bonus=1 

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
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean	: clean
	@$(RM) $(NAME) $(LIBFT) $(BONUS)

re		: fclean
	$(MAKE) all

.PHONY	: all clean fclean re $(dir $(LIBFT)) bonus
