/*
** events.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Feb 25 19:37:10 2017 
** Last update Sun Feb 26 17:08:30 2017 
*/
#include <ncurses.h>
#include "tetris.h"

void	my_pause(t_tetris *tetris)
{
  mvprintw(0, 0, "pause");
}

void	my_quit(t_tetris *tetris)
{
  mvprintw(0, 0, "quit");
}
