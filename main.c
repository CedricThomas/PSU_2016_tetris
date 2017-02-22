/*
** main.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Feb 22 09:46:31 2017 
** Last update Wed Feb 22 09:46:35 2017 
*/

#include <stdlib.h>
#include "tetris.h"
#include "my.h"

int	help(int jump)
{
  if (jump == 1)
    my_putchar('\n');
  my_putstr("Usage: ./tetris [option]\nOptions:\n");
  my_putstr("  --help\t\tDisplay this help\n");
  my_putstr("  -l --level={num}\tStart at level num\n");
  my_putstr("  -kl –-key-left={K}");
  my_putstr("\tMove tetrimino on LEFT using key K\n");
  my_putstr("  -kr –-key-right={K}");
  my_putstr("\tMove tetrimino on RIGHT using key K\n");
  my_putstr("  -kt –-key-top={K}");
  my_putstr("\tTurn tetrimino with key K\n");
  my_putstr("  -kd –-key-drop={K}");
  my_putstr("\tSet default DROP on key K\n");
  my_putstr("  -kq –-key-quit={K}");
  my_putstr("\tQuit program when press key K\n");
  my_putstr("  -kp –-key-pause={K}");
  my_putstr("\tPause and restart game when press key K\n");
  my_putstr("  --map-size={row,col}");
  my_putstr("\tSet game size at row, col\n");
  my_putstr("  -w –-without-next");
  my_putstr("\tHide next tetrimino\n");
  my_putstr("  -d –-debug\t\tDebug mode\n");
  return (0);
}

static void	  my_free_rule(t_game_rules *my_rules)
{
  free(my_rules->key_Left);
  free(my_rules->key_Right);
  free(my_rules->key_Turn);
  free(my_rules->key_Drop);
  free(my_rules->key_Quit);
  free(my_rules->key_Pause);
}

int		main(int ac, char **av)
{
  t_game_rules	my_rules;
  t_tetrimino	*form_list;

  if (ac == 2 && !my_strcmp("--help", av[1]))
    return (help(0));
  if (get_gamerules(&my_rules, av, ac) == 84)
    return (84);
  if (get_form(&form_list) == 84)
    return (84);
  //insérer ici la fonction de gestion du jeu.
  if (my_rules.debug == 1)
    debug_mode(form_list, &my_rules);
  //the_game(&my_rules, form_list);
  my_free_rule(&my_rules);
  free(form_list);
  return (0);
}
