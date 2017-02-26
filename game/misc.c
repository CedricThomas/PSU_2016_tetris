/*
** misc.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Feb 25 19:07:15 2017 
** Last update Sat Feb 25 19:19:42 2017 
*/
#include <stdlib.h>
#include "tetris.h"

int		setmap(t_tetris *tetris)
{
  int		y;
  int		x;

  if ((tetris->map = malloc(sizeof(char *) * (tetris->my_rules->map.y + 3)))
      == NULL)
    return (-1);
  y = -1;
  while (++y < tetris->my_rules->map.y + 2)
    {
      if ((tetris->map[y] =
	   malloc(sizeof(char) * (tetris->my_rules->map.x + 3))) == NULL)
	return (-1);
      x = -1;
      while (++x < tetris->my_rules->map.x + 2)
	{
	  if (y == 0  || y == tetris->my_rules->map.y + 1 ||
	      x == 0 || x == tetris->my_rules->map.x + 1)
	    tetris->map[y][x] = '#';
	  else
	    tetris->map[y][x] = ' ';
	}
      tetris->map[y][x] = 0;
    }
  tetris->map[y] = NULL;
  return (0);
}

