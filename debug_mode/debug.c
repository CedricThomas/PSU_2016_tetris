/*
** debug.c for DEBUG MODE in /home/Maxime/delivery/PSU/PSU_2016_tetris/debug_mode/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 09:16:27 2017 Maxime Jenny
** Last update Thu Mar  2 20:11:52 2017 
*/
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <termio.h>
#include "tetris.h"
#include "my.h"
#include "my_printf.h"

static char	*check_str(char *str)
{
  if (!my_strcmp(str, " "))
    return ("(space)");
  else
    return (str);
}

int		debug_mode(t_tetrimino *form_list, t_game_rules *my_rules)
{
  int		i;
  struct termio	termio;
  char		buf;

  my_printf("*** DEBUG MODE ***\n");
  my_printf("Key Left :  %s\n", check_str(my_rules->mkey_left));
  my_printf("Key Right :  %s\n", check_str(my_rules->mkey_right));
  my_printf("Key Turn :  %s\n", check_str(my_rules->mkey_turn));
  my_printf("Key Drop :  %s\n", check_str(my_rules->mkey_drop));
  my_printf("Key Quit :  %s\n", check_str(my_rules->mkey_quit));
  my_printf("Key Pause :  %s\n", check_str(my_rules->mkey_pause));
  my_printf("Next :  %s\n", my_rules->next ? ("Yes") : ("No"));
  my_printf("Level :  %d\n", my_rules->level);
  my_printf("Size :  %d*%d\n", my_rules->map.y, my_rules->map.x);
  i = -1;
  while (form_list[++i].name != NULL);
  my_printf("Tetriminos : %d\n", i);
  i = -1;
  while (form_list[++i].name != NULL)
    show_tetri(&form_list[i]);
  my_printf("Press any key to start Tetris\n");
  my_set_term(&termio);
  while (read(0, &buf, 1) == 0);
  my_reset_term(&termio);
}
