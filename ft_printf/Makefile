NAME			= printf.a

SRCS = srcs/ft_printf.c srcs/numbers.c srcs/characters.c srcs/ptr.c\

INCLUDES = include/ft_printf.h

OBJS := $(SRCS:%.c=%.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus
