/*
** sort.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Fri Feb 24 21:05:11 2017 
** Last update Wed Mar  1 15:28:29 2017 
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

int	check_color(t_tetrimino **shape_list)
{
  int	i;

  i = -1;
  setupterm(NULL, 0, NULL);
  start_color();
  while ((*shape_list)[++i].name != NULL)
    {
      if ((*shape_list)[i].color < 0 || (*shape_list)[i].color >= COLORS)
	(*shape_list)[i].valid = 0;
    }
  endwin();
  return (0);
}
