/*
** vector.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 22:37:31 2017
** Last update Wed Feb 22 00:57:10 2017
*/
#include "tetris.h"

t_vector2i	myvector2i(int x, int y)
{
  t_vector2i	vec;

  vec.x = x;
  vec.y = y;
  return (vec);
}
