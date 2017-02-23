/*
** time.c for time in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 14:57:00 2017 Maxime Jenny
** Last update Thu Feb 23 16:10:12 2017 Maxime Jenny
*/

#include <time.h>
#include "tetris.h"
#include "my_printf.h"

/*
** il faut set prec_time a 0 ainsi que first_time a 0
*/

int		set_time(t_time *t)
{
  t->first_time = 0;
  t->prec_time = 0;
  t->time_before_pause = 0;
  return (0);
}

int		find_time(t_time *t)
{
  time_t	the_time;

  the_time = time(NULL);
  if (t->first_time == 0)
    t->first_time = the_time;
  t->actual_time = the_time;
  return (0);
}

int			interpret_time(t_time *t)
{
  unsigned long long	tim_e;

  tim_e = t->actual_time - t->first_time + t->time_before_pause;
  if (t->prec_time != tim_e)
    my_printf("%lu:%lu:%lu\n", tim_e / 3600, tim_e / 60, tim_e % 60);
  t->prec_time = tim_e;
  return (0);
}
