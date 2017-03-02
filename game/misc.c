/*
** misc.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sat Feb 25 19:07:15 2017
** Last update Thu Mar  2 17:00:58 2017 
*/
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

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

static void	down_lines(t_tetris *tetris, int line)
{
  int		i;

  while (line > 0)
    {
      i = 0;
      while (tetris->map[line][++i] != '#')
	{
	  if (line != 1)
	    tetris->map[line][i] = tetris->map[line - 1][i];
	  else
	    tetris->map[line][i] = ' ';
	}
      line -= 1;
    }
}

int		del_full_lines(t_tetris *tetris)
{
  int		bool;
  int		y;
  int		x;

  y = 0;
  bool = 0;
  while (tetris->map[++y + 1])
    {
      x = 0;
      bool = 1;
      while (tetris->map[y][++x] != '#' && bool == 1)
	if (tetris->map[y][x] == ' ')
	  bool = 0;
      x = 0;
      while (tetris->map[y][++x] != '#' && bool)
	{
	  down_lines(tetris, y);
	  tetris->score += tetris->my_rules->map.x * SCORE_CUBE;
	  tetris->line += 1;
	  if (tetris->line % LINE_TO_UP == 0 && tetris->my_rules->level < 10)
	    tetris->my_rules->level += 1;
	  y = 0;
	}
    }
  return (0);
}

void	free_tetri(t_tetrimino *tet)
{
  free_tab(tet->matrix);
  free(tet->name);
  free(tet);
}

int		auto_drop(t_tetris *tetris)
{
  int           y;
  int           x;

  if (tetris->actual_tetri == NULL)
    return (84);
  if (tetris->cycle <= CYCLE_MAX - tetris->my_rules->level * CYCLE_ADD)
    tetris->cycle++;
  else
    {
      tetris->cycle = 0;
      my_drop(tetris);
    }
  return (0);
}
