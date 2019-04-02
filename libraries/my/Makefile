SRC	=	my_strlen.c		\
		my_memcpy.c		\
		my_strdup.c		\

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

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
