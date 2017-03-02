/*
** print.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 22:17:30 2017 
** Last update Thu Mar  2 10:33:01 2017 
*/
#include <curses.h>
#include "tetris.h"

void	print_map(t_tetris *tetris)
{
  int	i;
  int	j;
  char	charac;
  int	color;

  i = -1;
  while (tetris->map[++i])
    {
      j = -1;
      while (tetris->map[i][++j])
	{
	  color = (tetris->map[i][j] == '#' ? 7 : tetris->map[i][j]);
	  charac = '#';
	  if (tetris->map[i][j] == '#')
	    charac = '*';
	  attron(COLOR_PAIR(color));
	  mvprintw(i + tetris->pos_map.y, j + tetris->pos_map.x,
		   "%c", tetris->map[i][j]);
	  attroff(COLOR_PAIR(color));
	}
    }
}

int             my_put_tetri(t_tetrimino *tetri, t_vector2i rep, t_tetris *tetris)
{
  int           y;
  int           x;

  y = 0;
  while (tetri->matrix[y])
    {
      x = 0;
      while (tetri->matrix[y][x])
	{
	  if (tetri->matrix[y][x] != ' ')
	    {
	      attron(COLOR_PAIR(tetri->color));
	      mvprintw(y + rep.y + tetri->pos.y, x + rep.x + tetri->pos.x,
		       "%c", tetri->matrix[y][x]);
	      attroff(COLOR_PAIR(tetri->color));
	    }
	  x++;
	}
      y++;
    }
}

void	draw_border(t_vector2i point, t_vector2i size, int color)
{
  int	y;
  int	x;

  y = 0;
  while (y < size.y + 1)
    {
      x = 0;
      while (x < size.x + 1)
	{
	  attron(COLOR_PAIR(color));
	  if (x == 0 || x == size.x ||
	      y == size.y || y == 0)
	  mvprintw(y + point.y, x + point.x, "#");
	  attroff(COLOR_PAIR(color));
	  x++;
	}
      y++;
    }
}

int		draw_boards(t_tetris *tetris)
{
  t_vector2i	vec;

  vec = tetris->my_rules->map;
  vec = myvector2i(vec.x + vec.x / 2, vec.y / 2);
  vec = addvec(tetris->pos_map, vec);
  if (!tetris->my_rules->next)
    {
      draw_border(vec, addvec(tetris->next_tetri->size, myvector2i(7, 4)),
		  tetris->next_tetri->color);
      mvprintw(vec.y + 1, vec.x + 3, "Next");
      my_put_tetri(tetris->next_tetri, addvec(vec, myvector2i(4, 3)), tetris);
    }
}

int		print_game(t_tetris *tetris, t_tetrimino *shape_list)
{
  auto_drop(tetris);
  if (gen_tetri(tetris, shape_list) == -1)
    return (-1);
  print_map(tetris);
  my_put_tetri(tetris->actual_tetri, tetris->pos_map, tetris);
  draw_boards(tetris);
}
