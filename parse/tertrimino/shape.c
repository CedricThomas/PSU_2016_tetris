/*
** shape.c for  in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Feb 22 13:41:55 2017 
** Last update Sun Mar 12 15:04:53 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "tetris.h"
#include "get_next_line.h"

static t_vector2i	circle_height(char **tab)
{
  int			i;
  t_vector2i		max_len;

  max_len = myvector2i(-1, -1);
  i = -1;
  while (tab[++i])
    {
      if (max_len.x < 0 && is_in('*', tab[i]))
	max_len.x = i;
      if ((max_len.y < 0 && is_in('*', tab[i])) ||
	  (i > max_len.y && is_in('*', tab[i])))
	max_len.y = i;
    }
  return (max_len);
}

static t_vector2i	circle_width(char **tab)
{
  int			i;
  t_vector2i		vec;
  t_vector2i		max_len;

  max_len = myvector2i(-1, -1);
  i = -1;
  while (tab[++i])
    {
      vec = myvector2i(0, my_strlen(tab[i]) - 1);
      while (tab[i][vec.x] != '*' && tab[i][vec.x] && is_in('*', tab[i]))
	vec.x += 1;
      while (vec.y > 0 && tab[i][vec.y] != '*' && is_in('*', tab[i]))
	vec.y -= 1;
      if ((vec.x < max_len.x || max_len.x < 0) && is_in('*', tab[i]))
	max_len.x = vec.x;
      if (vec.y > max_len.y && is_in('*', tab[i]))
	max_len.y = vec.y;
    }
  return (max_len);
}

static int	fill_header(char **header, t_tetrimino **shape_list, int index)
{
  int		x;
  int		y;

  x = my_getnbr(header[0]);
  y = my_getnbr(header[1]);
  (*shape_list)[index].color = my_getnbr(header[2]);
  if (create_matrix(x, y, &(*shape_list)[index]))
    return (84);
  return (0);
}

static char	get_char(char *str, int index)
{
  char	c;

  c = ' ';
  if (my_strlen(str) - 1 >= index)
    c = str[index];
  return (c);
}

int		fill_shape(int fd, char **header,
			   int index, t_tetrimino **shape_list)
{
  int		i;
  int		j;
  t_vector2i	size_w;
  t_vector2i	size_h;
  char		**tab;

  if (fill_header(header, shape_list, index) == 84)
    return (84);
  if ((tab = fd_to_tab(fd, (*shape_list)[index].size.y)) == NULL)
    return (84);
  size_w = circle_width(tab);
  size_h = circle_height(tab);
  if (size_w.y - size_w.x + 1 != (*shape_list)[index].size.x ||
      size_h.y - size_h.x + 1 != (*shape_list)[index].size.y)
    return (84);
  i = -1;
  while (++i + size_h.x <= size_h.y)
    {
      j = -1;
      while (++j + size_w.x <= size_w.y)
	(*shape_list)[index].matrix[i][j] = get_char(tab[i + size_h.x],
						     j + size_w.x);
    }
  free_tab(tab);
  return (0);
}
