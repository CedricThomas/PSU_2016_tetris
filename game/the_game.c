/*
** the_game.c for THE GAME IS ON in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 08:50:45 2017 Maxime Jenny
** Last update Sun Mar 12 17:14:54 2017 Cédric Thomas
*/

#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <termio.h>
#include <time.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

int		my_print(t_tetris *tetris, t_tetrimino *shape_list)
{
  tetris->pos_map.x = tetris->term_size.x / 2 -
    (tetris->my_rules->map.x / 2 - 1);
  tetris->pos_map.y = tetris->term_size.y / 2 -
    (tetris->my_rules->map.y / 2 - 1);
  if (tetris->status == 0)
    {
      mvprintw(tetris->term_size.y / 2,
	       tetris->term_size.x / 2 - 5, "PAUSE");
      return (0);
    }
  if (tetris->term_size.x < tetris->my_rules->map.x + 2 ||
      tetris->term_size.y < tetris->my_rules->map.y + 2)
    my_pause(tetris);
  else
    if ((print_game(tetris, shape_list)) != 0)
      return (84);
  return (0);
}

static int	reset(t_input *my_inputs, struct termio termios)
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
  start_color();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_BLUE, COLOR_BLUE);
  init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(4, COLOR_GREEN, COLOR_GREEN);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_WHITE, COLOR_WHITE);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(9, 40, 40);
  tetris->line = 0;
  tetris->actual_tetri = NULL;
  tetris->next_tetri = NULL;
  tetris->cycle = 0;
  if ((tetris->t = malloc(sizeof(t_time))) == NULL)
    return (-1);
  tetris->t->time_before_pause = 0;
  set_time(tetris->t);
  return (0);
}

static void	detect_scr(t_tetris *tetris, int mod, struct winsize size)
{
  if (mod == 0)
    {
      tetris->term_size.x = -1;
      tetris->term_size.y = -1;
      return ;
    }
  if (size.ws_col != tetris->term_size.x
      || size.ws_row != tetris->term_size.y)
    clear();
}

int			the_game(t_tetris *tetris,
				 t_tetrimino *shape_list)
{
  t_input		my_inputs;
  struct winsize	size;
  struct termio		termios;

  srand(getpid() * time(NULL) * getpid() * 9 * time(NULL));
  detect_scr(tetris, 0, size);
  if (set_all(tetris) == -1 || set_input(&my_inputs, tetris) == 84)
    return (84);
  while (tetris->status != 2)
    {
      ioctl(0, TIOCGWINSZ, &size);
      detect_scr(tetris, 1, size);
      tetris->term_size = myvector2i(size.ws_col, size.ws_row);
      my_set_term(&termios);
      if (my_print(tetris, shape_list) == 84)
	return (84);
      if (try_input(&my_inputs, tetris) == 84)
	return (84);
      refresh();
    }
  return (reset(&my_inputs, termios));
}
