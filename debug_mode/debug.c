/*
** debug.c for DEBUG MODE in /home/Maxime/delivery/PSU/PSU_2016_tetris/debug_mode/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 09:16:27 2017 Maxime Jenny
** Last update Sat Mar 18 15:38:08 2017 
*/
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <termio.h>
#include "tetris.h"
#include "my.h"
#include "my_printf.h"

static void	print_key(char *key, char *value)
{
  int		i;

  i = -1;
  my_printf("Key %s :  ", key);
  while (value[++i])
    {
      if (value[i] == '\e')
	my_putstr("^E");
      else if (value[i] == ' ')
	my_putstr("(space)");
      else
	my_putchar(value[i]);
    }
  my_putchar('\n');
}

int		debug_mode(t_tetrimino *form_list, t_game_rules *my_rules)
{
  int		i;
  struct termio	termio;
  char		buf;

  my_printf("*** DEBUG MODE ***\n");
  print_key("Left", my_rules->mkey_left);
  print_key("Right", my_rules->mkey_right);
  print_key("Turn", my_rules->mkey_turn);
  print_key("Drop", my_rules->mkey_drop);
  print_key("Quit", my_rules->mkey_quit);
  print_key("Pause", my_rules->mkey_pause);
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
  return (0);
}
