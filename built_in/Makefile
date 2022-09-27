NAME		=	minishell

CC			= 	cc
CFLAGS		=	-Wall -Werror -Wextra

INCLUDE		=	../include
LIBFT		=	../libft

SRCS		= 	main.c\
				ft_cd.c\
				ft_echo.c\
				ft_env.c\
				ft_exit.c\
				ft_export.c\
				ft_pwd.c\
				ft_unset.c\
				../ft_lst_func.c

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
