/*
** nbr.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Feb 21 17:32:25 2017 
** Last update Tue Feb 21 17:41:23 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "tetris.h"

int	is_an_int(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (1);
  if (str[0] == '-')
    i += 1;
  while (str[i])
    {
      if (!is_nb(str[i]))
	return (1);
      i += 1;
    }
  return (0);
}
