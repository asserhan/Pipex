NAME	=	pipex
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
SRC		=	utils.c utils2.c ft_split.c processes.c pipex.c error.c
OBJ		=	$(SRC:.c=.o)

%.o: %.c pipex.h
			${CC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean bonus re


