/*
** tetra.c for tetra in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Mon Feb 27 22:05:39 2017 Maxime Jenny
** Last update Wed Mar  1 17:04:02 2017 Maxime Jenny
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "tetris.h"
#include "my.h"

t_tetrimino		*my_dup_tetra(t_tetrimino tet)
{
  t_tetrimino		*dup;
  int			y;

  if ((dup = malloc(sizeof(t_tetrimino))) == NULL)
    return (NULL);
  y = 0;
  dup->name = tet.name;
  dup->size.x = tet.size.x;
  dup->size.y = tet.size.y;
  dup->pos.x = tet.pos.x;
  dup->pos.y = tet.pos.y;
  dup->color = tet.color;
  if ((dup->matrix = malloc(sizeof(char *) * tet.size.y + 1)) == NULL)
    return (NULL);
  while (y < tet.size.y)
    {
      if ((dup->matrix[y] = malloc(my_strlen(tet.matrix[y])))
	  == NULL)
	return (NULL);
      dup->matrix[y] = my_strdup(tet.matrix[y]);
      y++;
    }
  return (dup);
}

t_tetrimino	*roll_a_tetra(t_tetrimino *shape_list, t_tetris *tetris,
			     t_tetrimino *tetra)
{
  int		i;
  int		tmp;
  int		good;

  i = 0;
  good = 0;
  while (shape_list[++i].name != NULL);
  while (!good)
    {
      tmp = rand() % i;
      if (shape_list[tmp].valid == 0)
	continue;
      good = 1;
    }
  if ((tetra = my_dup_tetra(shape_list[tmp])) == NULL)
    return (NULL);
  return (tetra);
}

int		my_put_tetra(t_tetrimino *tetra, int x, int y,
			     t_tetris *tetris)
{
  int		y1;
  int		x1;

  y1 = 0;
  while (y1 < tetra->size.y)
    {
      x1 = 0;
      while (tetra->matrix[y1][x1] != '\0')
	{
	  if (tetra->matrix[y1][x1] != ' ')
	    {
	      attron(COLOR_PAIR(tetra->color));
	      mvprintw(y + y1, x + x1, "%c", tetra->matrix[y1][x1]);
	      attroff(COLOR_PAIR(tetra->color));
	    }
	  x1++;
	}
      y1++;
    }
}

int		move_tetra(t_tetris *tetris)
{
  int		y;
  int		x;

  if (tetris->index <= tetris->levels[tetris->my_rules->level])
    tetris->index++;
  else
    {
      x = tetris->pos_tetra.x;
      y = tetris->pos_tetra.y + tetris->actual_tetra->size.y;
      tetris->index = 0;
      if (tetris->map[y][x] == ' ')
	{
	  tetris->pos_tetra.y += 1;
	}
    }
}

int		tetra(t_tetris *tetris, t_tetrimino *shape_list,
		      struct winsize size)
{
  if (tetris->actual_tetra == NULL)
    {
      tetris->pos_tetra.x = tetris->my_rules->map.x / 2;
      tetris->pos_tetra.y = 1;
      if (tetris->next_tetra != NULL)
	{
	  tetris->actual_tetra = tetris->next_tetra;
	  tetris->next_tetra = NULL;
	}
      else
	{
	  if ((tetris->actual_tetra =
	       roll_a_tetra(shape_list, tetris, tetris->actual_tetra)) == NULL)
	    return (-1);
	}
    }
  if (tetris->next_tetra == NULL)
    if ((tetris->next_tetra =
	 roll_a_tetra(shape_list, tetris, tetris->next_tetra)) == NULL)
	return (-1);
  move_tetra(tetris);
  my_put_tetra(tetris->actual_tetra, tetris->term_size.x / 2 -
	       tetris->my_rules->map.x + tetris->pos_tetra.x,
	       tetris->term_size.y / 2 - tetris->my_rules->map.y / 2 +
	       tetris->pos_tetra.y, tetris);
  my_put_tetra(tetris->next_tetra, tetris->term_size.x / 2 + tetris->my_rules->map.x,
        (tetris->term_size.y) / 2 - 13, tetris);
  return (0);
}
