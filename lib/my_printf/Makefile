##
## Makefile for Makefile in /home/cedric/lib
## 
## Made by Cédric Thomas
## Login   <cedric@epitech.net>
## 
## Started on  Sat Oct 22 10:37:32 2016 Cédric Thomas
## Last update Sun Dec 18 14:40:56 2016 Cédric Thomas
##

SRC	=	my_printf.c		\
		types/flags_char.c	\
		types/flags_int.c	\
		types/flags_pointer.c	\
		types/flags_base.c	\
		misc/print.c		\
		misc/convert.c		\
		misc/str.c		\
		misc/stru_fct.c		\
		format.c		\
		printformat.c

SRCMY	=	is_betw.c		\
		my_puterror.c		\
		free_tab.c		\
		is_nb.c			\
		is_in.c			\
		my_find_prime_sup.c	\
		my_memset.c		\
		my_getnbr.c		\
		my_isneg.c		\
		my_is_prime.c		\
		my_power_rec.c		\
		my_putchar.c		\
		my_put_nbr.c		\
		my_putstr.c		\
		my_revstr.c		\
		my_showmem.c		\
		my_showstr.c		\
		my_show_wordtab.c	\
		my_sort_int_tab.c	\
		my_split.c		\
		my_square_root.c	\
		my_strcapitalize.c	\
		my_strcat.c		\
		my_strcmp.c		\
		my_strcpy.c		\
		my_strdup.c		\
		my_str_isalpha.c	\
		my_str_islower.c	\
		my_str_isnum.c		\
		my_str_isprintable.c	\
		my_str_isupper.c	\
		my_strlen.c		\
		my_strlowcase.c		\
		my_strncat.c		\
		my_strncmp.c		\
		my_strncpy.c		\
		my_strstr.c		\
		my_str_to_wordtab.c	\
		my_strupcase.c		\
		my_strcatdup.c		\
		convert_base.c		\
		my_swap.c

OBJ	=	$(SRC:.c=.o) $(addprefix ../my/, $(SRCMY:.c=.o))

NAME	=	libmyprintf.a

INCLUDE =       -I ./

CFLAGS  +=       $(INCLUDE)

all:	$(NAME)

init:
	cp ../my/my.h .

$(NAME): $(OBJ)
	ar rc -o $(NAME) $(OBJ)
	cp my_printf.h ../../include
	cp libmyprintf.a ..
	cp ../my/my.h ../../include
	cp libmyprintf.a ..
clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONE: all clean fclean re
