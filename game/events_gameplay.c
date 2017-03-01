/*
** events.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sat Feb 25 19:37:10 2017
** Last update Tue Feb 28 21:10:25 2017 Maxime Jenny
*/
#include <ncurses.h>
#include "tetris.h"

void	my_left(t_tetris *tetris)
{
  int	x;
  int	y;

  x = tetris->pos_tetra.x;
  y = tetris->pos_tetra.y;
  if (tetris->map[y][x - 1] == ' ')
    tetris->pos_tetra.x -= 1;
}

void	my_right(t_tetris *tetris)
{
  int	x;
  int	y;

  x = tetris->pos_tetra.x + tetris->actual_tetra->size.x;
  y = tetris->pos_tetra.y;
  if (tetris->map[y][x] == ' ')
    tetris->pos_tetra.x += 1;
}

void	my_drop(t_tetris *tetris)
{
  mvprintw(0, 0, "drop");
}

void	my_turn(t_tetris *tetris)
{
  if (tetris->pos_tetra.x - (tetris->term_size.x - tetris->my_rules->map.x) +
      tetris->actual_tetra->size.y < tetris->my_rules->map.x + 1)
  rrotate_matrix(tetris->actual_tetra);
}
