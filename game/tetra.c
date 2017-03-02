/*
** tetra.c for tetra in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Mon Feb 27 22:05:39 2017 Maxime Jenny
** Last update Thu Mar  2 17:35:31 2017 
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "tetris.h"
#include "my.h"

t_tetrimino		*my_dup_tetri(t_tetrimino tet)
{
  t_tetrimino		*dup;
  int			y;

  if ((dup = malloc(sizeof(t_tetrimino))) == NULL)
    return (NULL);
  y = 0;
  dup->name = my_strdup(tet.name);
  dup->size.x = tet.size.x;
  dup->size.y = tet.size.y;
  dup->pos.x = 0;
  dup->pos.y = 0;
  dup->color = tet.color;
  if ((dup->matrix = malloc(sizeof(char *) * (tet.size.y + 1))) == NULL)
    return (NULL);
  while (tet.matrix[y] != NULL)
    {
      if ((dup->matrix[y] = malloc(my_strlen(tet.matrix[y])))
	  == NULL)
	return (NULL);
      dup->matrix[y] = my_strdup(tet.matrix[y]);
      y++;
    }
  dup->matrix[y] = NULL;
  return (dup);
}

static t_tetrimino	*roll_a_tetri(t_tetrimino *shape_list, t_tetris *tetris)
{
  t_tetrimino		*tetri;
  int			i;
  int			tmp;
  int			good;

  i = 0;
  good = 0;
  while (shape_list[++i].name != NULL);
  while (!good)
    {
      tmp = rand() % i;
      if (shape_list[tmp].valid == 1)
	good = 1;
    }
  if ((tetri = my_dup_tetri(shape_list[tmp])) == NULL)
    return (NULL);
  return (tetri);
}

int		gen_tetri(t_tetris *tetris, t_tetrimino *shape_list)
{
  if (tetris->actual_tetri == NULL)
    {
      if (tetris->next_tetri == NULL)
	{
	  if ((tetris->actual_tetri = roll_a_tetri(shape_list, tetris)) == NULL)
	    return (-1);
	}
      else
	{
	  tetris->actual_tetri = tetris->next_tetri;
	  tetris->next_tetri = NULL;
	}
      tetris->actual_tetri->pos = myvector2i(tetris->my_rules->map.x / 2
					     - tetris->actual_tetri->size.x / 2, 1);
      if (tetris->actual_tetri->pos.x == 0 || tetris->actual_tetri->pos.y == 0)
	tetris->actual_tetri->pos = myvector2i(1, 1);
    }
  if (tetris->next_tetri == NULL)
    if ((tetris->next_tetri = roll_a_tetri(shape_list, tetris)) == NULL)
      return (-1);
  if (try_tetri(tetris, tetris->actual_tetri))
    tetris->status = 2;
  return (0);
}

int		try_tetri(t_tetris *tetris, t_tetrimino *tetri)
{
  t_vector2i	map_size;
  int		i;
  int		j;
  int		im;
  int		jm;

  i = -1;
  if (tetri == NULL)
    return (84);
  map_size = tetris->my_rules->map;
  while (tetri->matrix[++i])
    {
      j = -1;
      while (tetri->matrix[i][++j])
	{
	  jm = j + tetri->pos.x;
	  im = i + tetri->pos.y;
	  if (!(im >= 0 && im < map_size.y + 1 && jm >= 0 && jm < map_size.x + 1)
	      || tetris->map[im][jm] != ' ' && tetri->matrix[i][j] != ' ')
	    return (84);
	}
    }
  return (0);
}

int	add_to_map(t_tetris *tetris, t_tetrimino *tetri)
{
  t_vector2i	map_size;
  int		i;
  int		j;
  int		im;
  int		jm;

  i = -1;
  if (tetri == NULL)
      return (84);
  map_size = tetris->my_rules->map;
  while (tetri->matrix[++i])
    {
      j = -1;
      while (tetri->matrix[i][++j])
	{
	  jm = j + tetri->pos.x;
	  im = i + tetri->pos.y;
	  if (tetris->map[im][jm] == ' ')
	    {
	      tetris->map[im][jm] = ' ';
	      if (tetri->matrix[i][j] != ' ')
		tetris->map[im][jm] = tetri->color;
	    }
	}
    }
}
