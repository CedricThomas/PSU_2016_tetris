##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Mon Feb  6 10:12:41 2017 
##

SRC	=

OBJ	=	$(SRC:.c=.o)

NAME	=

LIB_F	=	./lib/

LIB	=	-lmy -lmyprintf -lgnl

INCLUDE	=	-I./include/

CFLAGS	+=	 $(INCLUDE) -g	


all:		$(NAME)

$(NAME):	$(OBJ)
		make -C lib/GNL
		make -C lib/my
		make -C lib/my_printf
		gcc -o $(NAME) $(OBJ) -L$(LIB_F) $(LIB)

clean:
		make -C lib/GNL fclean
		make -C lib/my fclean
		make -C lib/my_printf fclean
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
