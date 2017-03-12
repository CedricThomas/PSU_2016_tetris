/*
** events.c for events in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Fri Feb 24 18:13:37 2017 Maxime Jenny
** Last update Sun Mar 12 14:55:56 2017 
*/

#include <sys/ioctl.h>
#include <ncurses.h>
#include <termio.h>
#include <curses.h>
#include <unistd.h>
#include <termio.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

int			my_set_term(struct termio *termios)
{
  ioctl(0, TCGETA, termios);
  termios->c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  termios->c_cc[VTIME] = 0;
  termios->c_cc[VMIN] = 0;
  ioctl(0, TCSETA, termios);
  return (0);
}

int			my_reset_term(struct termio *termios)
{
  ioctl(0, TCGETA, termios);
  termios->c_lflag |= (ICANON | ECHO | ECHOE | ISIG);
  ioctl(0, TCSETA, termios);
  return (0);
}

