##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## make
##

SRC	=	obj_string.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	libobj.a

all:	$(OBJ)
	ar rc $(NAME) *.o

$(NAME):	$(OBJ)
	ar rc $(NAME) *.o

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
