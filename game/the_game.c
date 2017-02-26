/*
** the_game.c for THE GAME IS ON in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 08:50:45 2017 Maxime Jenny
** Last update Sun Feb 26 17:23:19 2017 Maxime Jenny
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

  if (size.ws_col < tetris->my_rules->map.x + 3 ||
	 size.ws_row < tetris->my_rules->map.y)
    {
      mvprintw((size.ws_row / 2),
	       (size.ws_col / 2) - 13, "%s", "Please, resize your terminal.");
    }
  else
    {
      y = -1;
      while (++y < tetris->my_rules->map.y + 2)
	mvprintw((size.ws_row / 2) - (tetris->my_rules->map.y / 2) + y,
		 (size.ws_col / 2) - (tetris->my_rules->map.y / 2), "%s",
		 tetris->map[y]);
    }
}

int			the_game(t_tetris *tetris,
				 t_tetrimino *shape_list)
{
  t_input		my_inputs;
  struct winsize	size;
  struct termio		termios;
  WINDOW		*win;
  t_time		t;

  win = initscr();
  curs_set(0);
  keypad(win, 1);
  my_set_term(&termios);
  set_time(&t);
  if (set_input(&my_inputs, tetris) == 84)
    return (84);
  while (1)
    {
      try_input(&my_inputs, tetris);
      ioctl(0, TIOCGWINSZ, &size);
      my_print_map(tetris, size);
      refresh();
      clear();
    }
  reset_input(&my_inputs);
}
