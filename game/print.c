/*
** print.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  1 22:17:30 2017 
** Last update Sun Mar 12 17:16:26 2017 Cédric Thomas
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
	  charac = (tetris->map[i][j] == '#' ? '#' : ' ');
	  if (tetris->map[i][j] != charac)
	    charac = '*';
	  attron(COLOR_PAIR(color));
	  mvprintw(i + tetris->pos_map.y, j + tetris->pos_map.x,
		   "%c", charac);
	  attroff(COLOR_PAIR(color));
	}
    }
}

int             my_put_tetri(t_tetrimino *tetri,
			     t_vector2i rep,
			     t_tetris *tetris)
{
  int           y;
  int           x;

  y = 0;
  (void)tetris;
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
  return (0);
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
	  if (x == 0 || x == size.x ||
	      y == size.y || y == 0)
	    {
	      attron(COLOR_PAIR(color));
	      mvprintw(y + point.y, x + point.x, "#");
	      attroff(COLOR_PAIR(color));
	    }
	  else
	    mvprintw(y + point.y, x + point.x, " ");
	  x++;
	}
      y++;
    }
}

static void	draw_boards(t_tetris *tetris, t_tetrimino *shape_list)
{
  t_vector2i	vec;
  t_vector2i	temp;

  vec = tetris->my_rules->map;
  vec = myvector2i(vec.x + 3, 0);
  vec = addvec(tetris->pos_map, vec);
  temp = addvec(get_max(shape_list), myvector2i(7, 4));
  if (tetris->my_rules->next == 1)
    {
      draw_border(vec, temp,
		  tetris->next_tetri->color);
      mvprintw(vec.y + 1, vec.x + 3, "Next");
      my_put_tetri(tetris->next_tetri, addvec(vec, myvector2i(4, 3)), tetris);
    }
  vec.y += temp.y + 2;
  draw_border(vec, myvector2i(20, 8),
	      tetris->actual_tetri->color);
  mvprintw(vec.y + 2, vec.x + 2, "Time : ");
  find_time(tetris->t);
  interpret_time(tetris->t, myvector2i(vec.x + 9, vec.y + 2));
  mvprintw(vec.y + 4, vec.x + 2, "Score : %d", tetris->score);
  mvprintw(vec.y + 6, vec.x + 2, "Level : %d", tetris->my_rules->level);
}

int		print_game(t_tetris *tetris, t_tetrimino *shape_list)
{
  if (gen_tetri(tetris, shape_list) == -1)
    return (-1);
  print_map(tetris);
  my_put_tetri(tetris->actual_tetri, tetris->pos_map, tetris);
  draw_boards(tetris, shape_list);
  del_full_lines(tetris);
  auto_drop(tetris);
  return (0);
}
