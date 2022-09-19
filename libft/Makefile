NAME = libft.a

CC = cc -g
CFLAG = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcu

SRCS_1	= ft_strlen.c		\
		  ft_strlcpy.c		\
		  ft_strlcat.c		\
		  ft_strchr.c		\
		  ft_strichr.c		\
		  ft_strnstr.c		\
		  ft_strncmp.c		\
		  ft_strdup.c		\
		  ft_strndup.c		\
		  ft_strrchr.c		\
		  ft_memset.c		\
		  ft_memcpy.c		\
		  ft_memmove.c		\
		  ft_memchr.c		\
		  ft_memcmp.c		\
		  ft_bzero.c		\
		  ft_atoi.c			\
		  ft_calloc.c		\
		  ft_isalnum.c		\
		  ft_isalpha.c		\
		  ft_isascii.c		\
		  ft_isdigit.c		\
		  ft_isprint.c		\
		  ft_strdup.c		\
		  ft_tolower.c		\
		  ft_toupper.c		\
		  get_next_line.c	\
		  get_next_line_utils.c
			
SRCS_2	= ft_substr.c		\
		  ft_strjoin.c		\
		  ft_strjoin_free.c	\
		  ft_strtrim.c		\
		  ft_striteri.c		\
		  ft_split.c		\
		  ft_strmapi.c		\
		  ft_itoa.c			\
		  ft_putchar_fd.c	\
		  ft_putstr_fd.c	\
		  ft_putendl_fd.c	\
		  ft_putnbr_fd.c	\

SRCS	= $(SRCS_1)			\
	  		$(SRCS_2)		\

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BN:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@ -I libft.h

clean :
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

 .PHONY : all clean fclean re