/*
** matrix.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Feb 22 15:21:00 2017
** Last update Thu Mar  2 16:41:04 2017 
*/
#include <stdlib.h>
#include "my_printf.h"
#include "my.h"
#include "tetris.h"

int	create_matrix(int x, int y, t_matrix *matrix)
{
  int           i;
  int           j;

  i = 0;
  matrix->size.x = x;
  matrix->size.y = y;
  matrix->pos = myvector2i(0, 0);
  if ((matrix->matrix = malloc(sizeof(int *) * (y + 1))) == NULL)
    return (1);
  while (i < y)
    {
      j = 0;
      if ((matrix->matrix[i] = malloc(sizeof(int) * (x + 1))) == NULL)
	return (1);
      while (j < x)
	{
	  matrix->matrix[i][j] = 0;
	  j += 1;
	}
      matrix->matrix[i][j] = 0;
      i += 1;
    }
  matrix->matrix[i] = NULL;
  return (0);
}

int	show_tetri(t_matrix *matrix)
{
  my_printf("Tetriminos : Name %s : ", matrix->name);
  if (matrix->valid)
    {
      my_printf("Size %d*%d : Color %d :\n",
		matrix->size.x, matrix->size.y, matrix->color);
      my_show_wordtab(matrix->matrix);
    }
  else
    {
      my_printf("Error\n");
      return (84);
    }
  return (0);
}

int	rrotate_matrix(t_matrix *matrix)
{
  int           i;
  int           j;
  char		**new;

  my_swap(&(matrix->size.x), &(matrix->size.y));
  if ((new = malloc(sizeof(char *) * (matrix->size.y + 1))) == NULL)
    return (84);
  i = -1;
  while (++i < matrix->size.y)
    {
      if ((new[i] = malloc(sizeof(char) * (matrix->size.x + 1))) == NULL)
	return (84);
      j = -1;
      while (++j < matrix->size.x)
	new[i][j] = matrix->matrix[matrix->size.x - j - 1][i];
      new[i][j] = 0;
    }
  new[i] = NULL;
  free_tab(matrix->matrix);
  matrix->matrix = new;
  return (0);
}

t_vector2i      get_max(t_matrix *matrix)
{
  int		i;
  t_vector2i	max;

  max = myvector2i(-1, -1);
  i = -1;
  while (matrix[++i].name != NULL)
    {
      if ((max.x == -1 || max.x < matrix[i].size.x) && matrix[i].valid)
	max.x = matrix[i].size.x;
      if ((max.y == -1 || max.y < matrix[i].size.y) && matrix[i].valid)
	max.y = matrix[i].size.y;
    }
  return (max);
}
