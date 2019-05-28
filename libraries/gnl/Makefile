## GNU CCC 2019
## LIBGNL

SRC	=	get_next_line.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libgnl.a

CRESET	=

.SILENT:
all:		$(OBJ)
		@printf "|------- Compiling libgnl.a\n$(CRESET)"
		ar rc $(NAME) *.o

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
