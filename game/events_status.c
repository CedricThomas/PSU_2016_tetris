/*
** events.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sat Feb 25 19:37:10 2017
** Last update Thu Mar  2 13:54:27 2017 
*/
#include <ncurses.h>
#include "tetris.h"

void	my_pause(t_tetris *tetris)
{
  if (tetris->status == 1)
    {
      tetris->t->time_before_pause  = tetris->t->prec_time;
      tetris->status = 0;
    }
  else
    {
      set_time(tetris->t);
      tetris->status = 1;
    }
}

void	my_quit(t_tetris *tetris)
{
  tetris->status = 2;
}
