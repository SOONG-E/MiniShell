.DEFAULT_GOAL = all

NAME		=	minishell
BONUS	= minishell_bonus
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP
CPPFLAGS	=	-I./include -I$(HOME)/homebrew/opt/readline/include
LDFLAGS		=	-L./libft -L$(HOME)/homebrew/opt/readline/lib
LDLIBS		=	-lft -lreadline
RM			=	rm -rf

OUTDIR		=	out/

LIBFT		=	./libft/libft.a

SRCS		= 	mandatory/main.c							\
				mandatory/parse_line.c					\
				mandatory/replace_space.c					\
				mandatory/replace_op.c					\
				mandatory/expand_env.c					\
				mandatory/expand_env_utils.c				\
				mandatory/manage_symbol.c					\
				mandatory/manage_envlst.c					\
				mandatory/manage_error.c					\
				mandatory/manage_env.c					\
				mandatory/manage_mem.c					\
				mandatory/manage_signal.c					\
				mandatory/symbolize.c						\
				mandatory/preprocess_line.c				\
				mandatory/check_cmd.c						\
				mandatory/validate.c						\
				mandatory/validate_utils.c				\
				mandatory/manage_info.c					\
				mandatory/expand_filename.c				\
				mandatory/delete_quote.c					\
				mandatory/execute.c						\
				mandatory/token_tree/and_or.c				\
				mandatory/token_tree/brace_group.c		\
				mandatory/token_tree/make_parse_tree.c	\
				mandatory/token_tree/pipeline.c			\
				mandatory/token_tree/utils.c				\
				mandatory/execute_pipe_line.c				\
				mandatory/execute_pipe_line_utils.c		\
				mandatory/execute_pipe_line_io.c			\
				mandatory/execute_pipe_line_io_utils.c	\
				mandatory/execute_single_commend.c		\
				mandatory/replace_wild_card.c				\
				mandatory/make_env.c						\
				mandatory/built_in/ft_cd.c				\
				mandatory/built_in/ft_cd_utils.c			\
				mandatory/built_in/ft_echo.c				\
				mandatory/built_in/ft_env.c				\
				mandatory/built_in/ft_exit.c				\
				mandatory/built_in/ft_export.c			\
				mandatory/built_in/ft_pwd.c				\
				mandatory/built_in/ft_unset.c				\
				mandatory/built_in/ft_pipe_export.c						

BONUS_SRCS		= 	bonus/main_bonus.c					\
				bonus/parse_line_bonus.c					\
				bonus/replace_space_bonus.c				\
				bonus/replace_op_bonus.c					\
				bonus/expand_env_bonus.c					\
				bonus/expand_env_utils_bonus.c			\
				bonus/manage_symbol_bonus.c				\
				bonus/manage_envlst_bonus.c				\
				bonus/manage_error_bonus.c				\
				bonus/manage_env_bonus.c					\
				bonus/manage_mem_bonus.c					\
				bonus/manage_signal_bonus.c				\
				bonus/symbolize_bonus.c					\
				bonus/preprocess_line_bonus.c				\
				bonus/check_cmd_bonus.c					\
				bonus/validate_bonus.c					\
				bonus/validate_utils_bonus.c				\
				bonus/manage_info_bonus.c					\
				bonus/expand_filename_bonus.c				\
				bonus/delete_quote_bonus.c				\
				bonus/execute_bonus.c						\
				bonus/token_tree/and_or_bonus.c			\
				bonus/token_tree/brace_group_bonus.c		\
				bonus/token_tree/make_parse_tree_bonus.c	\
				bonus/token_tree/pipeline_bonus.c			\
				bonus/token_tree/utils_bonus.c			\
				bonus/execute_pipe_line_bonus.c			\
				bonus/execute_pipe_line_utils_bonus.c		\
				bonus/execute_pipe_line_io_bonus.c		\
				bonus/execute_pipe_line_io_utils_bonus.c	\
				bonus/execute_single_commend_bonus.c		\
				bonus/replace_wild_card_bonus.c			\
				bonus/make_env_bonus.c					\
				bonus/built_in/ft_cd_bonus.c				\
				bonus/built_in/ft_cd_utils_bonus.c		\
				bonus/built_in/ft_echo_bonus.c			\
				bonus/built_in/ft_env_bonus.c				\
				bonus/built_in/ft_exit_bonus.c			\
				bonus/built_in/ft_export_bonus.c			\
				bonus/built_in/ft_pwd_bonus.c				\
				bonus/built_in/ft_unset_bonus.c			\
				bonus/built_in/ft_pipe_export_bonus.c

OBJS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.o))
BONUS_OBJS		=	$(addprefix $(OUTDIR),$(BONUS_SRCS:%.c=%.o))
DEPS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.d))
-include $(DEPS)

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

bonus : $(BONUS)

$(BONUS) : $(BONUS_OBJS)
	$(MAKE) -C $(dir $(LIBFT))
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

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