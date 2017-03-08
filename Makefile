##
## Makefile for Makefile in /home/cedric/lib
##
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
##
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Wed Mar  8 10:13:45 2017 
##

SRC	=	main.c				\
		math/vector.c			\
		math/matrix.c			\
		misc/nbr.c			\
		misc/str.c			\
		parse/match.c			\
		parse/args/args.c		\
		parse/args/values.c		\
		parse/args/prepare.c		\
		parse/args/type.c		\
		parse/tertrimino/tetris.c	\
		parse/tertrimino/shape.c	\
		parse/tertrimino/misc.c		\
		parse/tertrimino/sort.c		\
		debug_mode/debug.c		\
		game/the_game.c			\
		game/misc.c			\
		game/time.c			\
		game/term.c			\
		game/events_gameplay.c		\
		game/events_status.c		\
		game/input.c			\
		game/tetra.c			\
		game/print.c			\

OBJ	=	$(SRC:.c=.o)

NAME	=	tetris

LIB_F	=	./lib/

LIB	=	-lmy -lmyprintf -lgnl -lncurses

INCLUDE	=	-I./include/

CFLAGS	+=	 $(INCLUDE) -g


all:		$(NAME)

$(NAME):	$(OBJ)
		make -sC lib/GNL
		make -sC lib/my
		make -sC lib/my_printf
		gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)

clean:
		make -sC lib/GNL fclean
		make -sC lib/my fclean
		make -sC lib/my_printf fclean
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
