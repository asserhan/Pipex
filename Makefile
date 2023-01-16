NAME	=	pipex
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
SRC		=	ft_strncmp.c ft_split.c  ft_memcpy.c ft_strdup.c ft_strlcpy.c ft_strlen.c ft_substr.c \
			ft_strjoin.c pipex.c error.c
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


