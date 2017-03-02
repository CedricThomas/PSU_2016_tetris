/*
** events.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sat Feb 25 19:37:10 2017
** Last update Thu Mar  2 09:47:59 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "tetris.h"
#include "my.h"

void	my_left(t_tetris *tetris)
{
  if (tetris->actual_tetri == NULL)
    return ;
  tetris->actual_tetri->pos.x -= 1;
  if (try_tetri(tetris, tetris->actual_tetri))
    tetris->actual_tetri->pos.x += 1;
}

void	my_right(t_tetris *tetris)
{
  if (tetris->actual_tetri == NULL)
      return ;
  tetris->actual_tetri->pos.x += 1;
  if (try_tetri(tetris, tetris->actual_tetri))
    tetris->actual_tetri->pos.x -= 1;
}

void	my_drop(t_tetris *tetris)
{
  if (tetris->actual_tetri == NULL)
    return ;
  tetris->actual_tetri->pos.y += 1;
  if (try_tetri(tetris, tetris->actual_tetri))
    {
      tetris->actual_tetri->pos.y -= 1;
      add_to_map(tetris, tetris->actual_tetri);
      free_tab(tetris->actual_tetri->matrix);
      free(tetris->actual_tetri->name);
      free(tetris->actual_tetri);
      tetris->actual_tetri = NULL;
    }
}

void		my_turn(t_tetris *tetris)
{
  t_tetrimino	*tetri;

  if (tetris->actual_tetri == NULL)
      return ;
  if ((tetri = my_dup_tetri(*(tetris->actual_tetri))) == NULL)
    exit(84);
  rrotate_matrix(tetri);
  tetri->pos = tetris->actual_tetri->pos;
  if (try_tetri(tetris, tetri))
    {
      free_tab(tetri->matrix);
      free(tetri->name);
      free(tetri);
    }
  else
    {
      free_tab(tetris->actual_tetri->matrix);
      free(tetris->actual_tetri->name);
      free(tetris->actual_tetri);
      tetris->actual_tetri = tetri;
    }
}
