/*
** the_game.c for THE GAME IS ON in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 08:50:45 2017 Maxime Jenny
** Last update Thu Feb 23 18:13:21 2017 Maxime Jenny
*/

#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

int			my_set_term(struct termios *termios)
{
  ioctl(0, TCGETA, termios);
  termios->c_lflag &= ~(ICANON|ECHO);
  if (termios->c_lflag & ICANON)
    printf("1\n");
  else
    printf("0\n");
}

int			the_game(t_game_rules *my_rules,
				 t_tetrimino *shape_list)
{
  struct winsize	size;
  struct termios	termios;
  int			event;
  WINDOW		*win;
  t_time		t;

  // win = initscr();
  // curs_set(0);
  // keypad(win, 1);
  // my_set_term(&termios);
  // set_time(&t);
  // while (1)
  //   {
  //     ioctl(0, TIOCGWINSZ, &size);
  //     // my_print_map(&t, size, my_rules);
  //     refresh();
  //     event = getch();
  //     printw("%d", event);
  //     // ici fonction qui réccupère les events.
  //     clear();
  //     if (event == 27)
  // return (0);
  //   }
}
