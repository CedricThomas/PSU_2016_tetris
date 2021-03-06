/*
** sort.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Fri Feb 24 21:05:11 2017
** Last update Thu Mar 16 10:32:44 2017 
*/
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

static void	swap_tetri(t_tetrimino **shape_list, int index1, int index2)
{
  t_tetrimino	temp;

  temp = (*shape_list)[index1];
  (*shape_list)[index1] = (*shape_list)[index2];
  (*shape_list)[index2] = temp;
}

void	sort_tetri(t_tetrimino **shape_list)
{
  int	i;
  int	action;

  action = 1;
  while (action)
    {
      i = 0;
      action = 0;
      while ((*shape_list)[i].name && (*shape_list)[++i].name != NULL)
	{
	  if ((*shape_list)[i - 1].name &&
	      my_strcmp((*shape_list)[i - 1].name, (*shape_list)[i].name) > 0)
	    {
	      action = 1;
	      swap_tetri(shape_list, i - 1, i);
	    }
	}
    }
}

static void	check_content(t_tetrimino **shape_list, int idx)
{
  int		i;
  int		j;

  i = -1;
  while ((*shape_list)[idx].matrix[++i] && (*shape_list)[idx].valid)
    {
      j = -1;
      while ((*shape_list)[idx].matrix[i][++j] && (*shape_list)[idx].valid)
	if (!is_in((*shape_list)[idx].matrix[i][j], " *"))
	    (*shape_list)[idx].valid = 0;
    }
}

int		check_tetri(t_tetrimino **shape_list, t_game_rules *rules)
{
  int		i;
  t_vector2i	vec;

  i = -1;
  while ((*shape_list)[++i].name != NULL)
    {
      if ((*shape_list)[i].valid)
	{
	  vec = rules->map;
	  if ((*shape_list)[i].color <= 0)
	    (*shape_list)[i].valid = 0;
	  else if ((*shape_list)[i].color > NB_COLORS)
	    (*shape_list)[i].color %= NB_COLORS;
	  if (has_colors())
	    (*shape_list)[i].color = 0;
	  if ((*shape_list)[i].size.x > vec.x ||
	      (*shape_list)[i].size.y > vec.y)
	    (*shape_list)[i].valid = 0;
	  check_content(shape_list, i);
	}
    }
  return (0);
}
