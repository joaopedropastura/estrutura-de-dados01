SRCS =		main.cpp

NAME =		vect_lib.a

CC =		g++ -std=c++17

CFLAGS =	-Wall -Wextra -Werror

OBJS =		$(SRCS:.cpp=.o)

RM =		rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	$(OBJS) ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:		$(RM) $(OBJS)

fclean:		clean $(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re