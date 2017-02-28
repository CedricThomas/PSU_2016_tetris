/*
** the_game.c for THE GAME IS ON in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 08:50:45 2017 Maxime Jenny
** Last update Mon Feb 27 22:13:57 2017 Maxime Jenny
*/

#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <termio.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

void		my_print_map(t_tetris *tetris, struct winsize size)
{
  int		y;

  if (tetris->status == 1)
    {
      if (size.ws_col < tetris->my_rules->map.x + 2 ||
	  size.ws_row < tetris->my_rules->map.y + 2)
	{
          my_pause(tetris);
	}
      else
	{
	  find_time(tetris->t);
	  interpret_time(tetris->t);
	  tetris->status = 1;
	  y = -1;
	  while (++y < tetris->my_rules->map.y + 2)
	    mvprintw((size.ws_row / 2) - (tetris->my_rules->map.y / 2) + y,
		     (size.ws_col / 2) - (tetris->my_rules->map.y / 2), "%s",
		     tetris->map[y]);
	}
    }
  else if (tetris->status == 0)
    mvprintw((size.ws_row / 2), (size.ws_col / 2) - 5, "%s", "PAUSE");
}

int			reset(t_input *my_inputs, t_tetris *tetris,
			      struct termio termios)
{
  reset_input(my_inputs);
  my_reset_term(&termios);
  return (0);
}

int			set_all(t_tetris *tetris)
{
  WINDOW		*win;

  win = initscr();
  curs_set(0);
  keypad(win, 1);
  mvprintw(10, 10, "00:00:00");
  if ((tetris->t = malloc(sizeof(t_time))) == NULL)
    return (-1);
  tetris->t->time_before_pause = 0;
  set_time(tetris->t);
  return (0);
}

int			the_game(t_tetris *tetris,
				 t_tetrimino *shape_list)
{
  t_input		my_inputs;
  struct winsize	size;
  struct termio		termios;
  int			game;

  game = 1;
  if (set_all(tetris) == -1 || set_input(&my_inputs, tetris) == 84)
    return (84);
  while (game)
    {
      my_set_term(&termios);
      try_input(&my_inputs, tetris);
      game = (tetris->status == 2) ? 0 : 1;
      ioctl(0, TIOCGWINSZ, &size);
      my_print_map(tetris, size);
      tetra(tetris, shape_list);
      refresh();
      clear();
    }
  return (reset(&my_inputs, tetris, termios));
}
