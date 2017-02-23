/*
** debug.c for DEBUG MODE in /home/Maxime/delivery/PSU/PSU_2016_tetris/debug_mode/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 09:16:27 2017 Maxime Jenny
** Last update Wed Feb 22 17:15:02 2017 
*/

#include <stdlib.h>
#include "tetris.h"
#include "my.h"
#include "my_printf.h"

int	debug_mode(t_tetrimino *form_list, t_game_rules *my_rules)
{
  int	i;

  i = -1;
  my_printf("*** DEBUG MODE ***\n");
  my_printf("Key Left :   %s\n", my_rules->key_Left);
  my_printf("Key Right :   %s\n", my_rules->key_Right);
  my_printf("Key Turn :   %s\n", my_rules->key_Turn);
  my_printf("Key Drop :   %s\n", my_rules->key_Drop);
  my_printf("Key Quit :   %s\n", my_rules->key_Quit);
  my_printf("Key Pause :   %s\n", my_rules->key_Pause);
  my_printf("Next :   %s\n", (my_rules->next) ? ("Yes") : ("No"));
  my_printf("Level :   %d\n", my_rules->level);
  my_printf("Size :   %d*%d\n", my_rules->map.x, my_rules->map.y);
  while (form_list[++i].name != NULL)
    show_tetri(&form_list[i]);
}
