NAME		=	minishell

CC			= 	cc -g
CFLAGS		=	-Wall -Werror -Wextra

INCLUDE		=	include
LIBFT		=	libft

SRCS		= 	main.c			\
				ft_lst_func.c

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
