NAME	=	pipex
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
SRC_F	=	utils.c utils2.c ft_split.c free.c processes.c pipex.c
SRC		= 	$(addprefix mandatory/, $(SRC_F))
BSRC_F	=	utils.c ft_split.c get_next_line.c get_next_line_utils.c here_doc.c free.c processes.c pipex.c
BSRC	=	$(addprefix bonus/, $(BSRC_F))
OBJ		=	$(SRC:.c=.o)
BOBJ	=	$(BSRC:.c=.o)

%.o: %.c mandatory/pipex.h bonus/pipex_bonus.h
			${CC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

bonus:		$(BOBJ)
			$(CC) $(BOBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)
			$(RM) $(BOBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean bonus re


