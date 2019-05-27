## GNU GPL3 2019
## Costa Bushnaq
## LIBOBJ

SRC	=	obj_string.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libobj.a

CRESET	=

.SILENT:
all:		$(OBJ)
		@printf "|------- Compiling libobj.a\n$(CRESET)"
		ar rc $(NAME) *.o

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
