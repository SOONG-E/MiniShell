NAME		=	minishell

CC			= 	cc
CFLAGS		=	-Wall -Werror -Wextra

INCLUDE		=	include
LIBFT		=	libft

SRCS		= 	main.c			\
				ft_lst_func.c	\
				parsing_cmd.c	\
				ft_env_split.c	\
				replace_space.c	\
				sub_env.c		\
				task_error.c	\
				test_ft.c		\
				manage_env.c	\
				manage_mem.c	\
				symbolizing.c	\
				preprocess_str.c

OBJS		=	$(SRCS:%.c=%.o)

all		: $(NAME)

$(NAME) : $(OBJS)
			make -C $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT) -lft -I $(INCLUDE) -lreadline

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
