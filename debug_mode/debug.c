/*
** debug.c for DEBUG MODE in /home/Maxime/delivery/PSU/PSU_2016_tetris/debug_mode/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Wed Feb 22 09:16:27 2017 Maxime Jenny
** Last update Wed Feb 22 09:38:12 2017 Maxime Jenny
*/

#include <stdlib.h>
#include "tetris.h"
#include "my.h"
#include "my_printf.h"

int	debug_mode(t_tetrimino *form_list, t_game_rules *my_rules)
{
  my_printf("*** DEBUG MODE ***\n");
  my_printf("Key Left :   %s\n", my_rules->key_Left);
  my_printf("Key Right :   %s\n", my_rules->key_Right);
  my_printf("Key Turn :   %s\n", my_rules->key_Turn);
  my_printf("Key Drop :   %s\n", my_rules->key_Drop);
  my_printf("Key Quit :   %s\n", my_rules->key_Quit);
  my_printf("Key Pause :   %s\n", my_rules->key_Pause);
  my_printf("Next :   %s\n", (my_rules->next) ? ("Yes") : ("No"));
  my_printf("Level :   %d\n", my_rules->level);
  my_printf("Size :   %d*%d", my_rules->map.x, my_rules->map.y);
  // my_printf("Tertriminos :   %d\n");
}
