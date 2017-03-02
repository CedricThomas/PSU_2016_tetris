/*
** vector.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 22:37:31 2017
** Last update Wed Mar  1 23:21:23 2017 
*/
#include "tetris.h"

t_vector2i	myvector2i(int x, int y)
{
  t_vector2i	vec;

  vec.x = x;
  vec.y = y;
  return (vec);
}

t_vector2i	addvec(t_vector2i vec1, t_vector2i vec2)
{
  t_vector2i	sum;

  sum.x = vec1.x + vec2.x;
  sum.y = vec1.y + vec2.y;
  return (sum);
}
