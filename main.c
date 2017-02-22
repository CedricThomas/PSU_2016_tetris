/*
** main.c for main.c in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Wed Feb 22 00:23:16 2017 
*/
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

static int	help()
{
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
    return (help());
  if (get_gamerules(&my_rules, av, ac) == 84)
    return (84);
  if (get_form(&form_list) == 84)
    return (84);
  my_free_rule(&my_rules);
  free(form_list);
  return (0);
}
