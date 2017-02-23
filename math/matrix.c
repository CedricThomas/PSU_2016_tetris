/*
** matrix.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Feb 22 15:21:00 2017 
** Last update Wed Feb 22 17:58:58 2017 
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
  int           i;
  int           j;

  i = 0;
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
