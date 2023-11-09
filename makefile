SRCS	= main.c set.c exe.c signal.c signal1.c free.c prase.c prase_write.c split_cmd.c split_cmd1.c \
		utils.c ft_split.c strjoin.c ft_printf.c pip.c redir.c \
		buin_env.c buin_cd.c buin_pwd.c buin_export.c buin_export1.c buin_exit.c buin_unset.c buin_echo.c
OBJS	= $(SRCS:.c=.o)
INCL	= ./
NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -lreadline
CC		= cc


all:$(NAME)

$(NAME):$(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -I $(INCL)

re:fclean all

fclean:clean
		rm -f $(NAME)

clean:
		rm -f $(OBJS)

.PHONY: clean fclean all re