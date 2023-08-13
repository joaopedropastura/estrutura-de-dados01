SRCS =		main.cpp

NAME =		vect_lib

CC =		g++

CFLAGS =	-Wall -Wextra -Werror

OBJS =		$(SRCS:.cpp=.o)

RM =		rm -f

.c.o:		${CC} ${CFLAGS} -c $< -o ${<:%.cpp=%.o}

all:		$(NAME)

$(NAME):	$(OBJS) ar rcs $(NAME) $(OBJS)

clean:		$(RM) $(OBJS)

fclean:		clean $(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re