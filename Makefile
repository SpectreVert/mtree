BUILDF		=	builds

SRCF		=	sources

INCLUDEF	=	includes

LIBF		=	libraries

H		:=	@

SLEEP_01	=	sleep 0.1

CRESET		=	#\e[0m

CR		=	#\e[1;91m

CG		=	#\e[1;92m

CW		=	#\e[1;90;97m

CY		=	#\e[1;93m

CB		=	#\e[1;94m

CCY		=	#\e[1;96m

SRC		=	$(SRCF)/main.c				\
			$(SRCF)/mtree.c				\
			$(SRCF)/tab.c				\

CC		=	gcc

NAME		=	mtree

CAZU_WARNINGS	=	-W 				\
			-Wall				\
			-Wextra				\

DBUG_WARNINGS	=	-Werror				\
			-Wparentheses			\
			-Wsign-compare			\
			-Wpointer-sign			\
			-Wuninitialized			\
			-Wunused-but-set-variable	\

DFLAGS		+=	-g -D DEBUG

CFLAGS		+=	-I $(INCLUDEF) -I $(LIBF)/my -I $(LIBF)/obj -fPIC $(CAZU_WARNINGS)

LFLAGS		+=	-L $(LIBF)/obj -L $(LIBF)/my -lobj -lmy -lncurses

OBJS		=	$(patsubst $(SRCF)/%.c, $(BUILDF)/%.o, $(SRC))

$(NAME):		$(BUILDF)/$(NAME)
			cp $(BUILDF)/$(NAME) .
			$(H)printf "$(CB)[INFO]$(CRESET) Build success!\n$(CRESET)"

$(BUILDF)/$(NAME):	$(OBJS)
			$(H)printf "|--- $(CW)Linking $(CR)objects$(CRESET)"
			$(H)printf " and $(CR)librairies$(CRESET)\n"
			$(H)printf "$(CRESET)"
			make -C $(LIBF)/obj 
			make -C $(LIBF)/my
			$(H) $(CC) -o $(BUILDF)/$(NAME) $(OBJS) $(LFLAGS)

$(BUILDF)/%.o:		$(SRCF)/%.c
			$(H)printf "|------- $(CW)Compiling [$(CG)$(notdir $<)$(CW)"
			$(H)printf " -> $(CR)$(notdir $@)$(CW)]\n$(CRESET)"
			$(H)mkdir -p $(dir $@)
			$(H) $(CC) -o $@ -c $< $(CFLAGS) $(LFLAGS)

.SILENT:
re:			fclean
			$(H)printf "$(CB)[INFO]$(CRESET) Starting build...\n"
			$(H)make all

all:			$(NAME)

debug:			CFLAGS += $(DFLAGS) $(DBUG_WARNINGS)

debug:			fclean debug_line $(NAME)

clean:
			$(H)printf "$(CB)[INFO]$(CRESET) Cleanin' shit...\n"
			$(H)printf "|--- $(CY)Cleaning objects.$(CRESET)\n"
			$(H)rm -rf $(OBJS)
			make -C $(LIBF)/obj clean
			make -C $(LIBF)/my clean

fclean:			clean
			$(H)printf "|--- $(CY)Cleaning binaries.$(CRESET)\n"
			$(H)rm -f $(BUILDF)/$(NAME)
			$(H)rm -f $(NAME)
			$(H)rm -f $(NAME)
			make -C $(LIBF)/obj fclean
			make -C $(LIBF)/my fclean

debug_line:
			$(H)printf "|--- $(CB)[INFO]$(CCY) Building debug mode.\n$(CRESET)"

prepare:
			$(H)printf "$(CB)[INFO]$(CRESET) Preparing folders"
			$(SLEEP_01)
			$(H)printf "."
			$(SLEEP_01)
			$(H)printf "."
			$(SLEEP_01)
			$(H)printf ".\n"
			$(SLEEP_01)
			mkdir -p $(INCLUDEF) $(SRCF) $(LIBF) $(BUILDF) $(TESTF)
			$(H)printf "$(CB)[INFO]$(CRESET) Building main.c file"
			$(SLEEP_01)
			$(H)printf "."
			$(SLEEP_01)
			$(H)printf "."
			$(SLEEP_01)
			$(H)printf ".\n"
			$(SLEEP_01)
			echo -ne "/*\n** EPITECH PROJECT, 2018\n** PROJECT_NAME\n** File description:\n** PROJECT_DESCRIPTION\n*/\n\nint main(int argc, char *argv[])\n{\n\treturn 0;\n}\n" > $(SRCF)/main.c
			$(H)printf "$(CB)[INFO]$(CRESET) All done!\n"

.PHONY: clean prepare fclean all re debug debug_line
