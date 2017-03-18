/*
** main.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Wed Feb 22 09:46:31 2017
** Last update Sat Mar 18 15:38:25 2017 
*/

#include <stdlib.h>
#include <ncurses.h>
#include "tetris.h"
#include "my.h"

int	help(int jump, char *name)
{
  if (jump == 1)
    my_putchar('\n');
  my_putstr("Usage:  ");
  my_putstr(name);
  my_putstr(" [options]\nOptions:\n");
  my_putstr("  --help\t\tDisplay this help\n");
  my_putstr("  -l --level={num}\tStart Tetris at level num (def:  1)\n");
  my_putstr("  -kl --key-left={K}\tMove the tetrimino LEFT ");
  my_putstr("using the K key (def:\tleft arrow)\n");
  my_putstr("  -kr --key-right={K}\tMove the tetrimino RIGHT ");
  my_putstr("using the K key (def:\tright arrow)\n");
  my_putstr("  -kt --key-turn={K}\tTURN the tetrimino clockwise ");
  my_putstr("90d using the K key (def:\ttop arrows)\n");
  my_putstr("  -kd --key-drop={K}");
  my_putstr("\tDROP the tetrimino using the K key (def:  down key)\n");
  my_putstr("  -kq --key-quit={K}");
  my_putstr("\tQUIT the game using the K key (def:  'Q' key)\n");
  my_putstr("  -kp --key-pause={K}");
  my_putstr("\tPAUSE/RESTART the game using the K key (def:  space bar)\n");
  my_putstr("  --map-size={row,col}\tSet the numbers of ");
  my_putstr("rows and colums of the map (def:  20,10)\n");
  my_putstr("  -w --without-next");
  my_putstr("\tHide next tetrimino (def:  false)\n");
  my_putstr("  -d --debug\t\tDebug mode (def:  false)\n");
  return (0);
}

static void	my_free_rule(t_game_rules *my_rules,
			     t_tetris tetris, t_tetrimino *shape_list)
{
  int		i;

  free(my_rules->mkey_left);
  free(my_rules->mkey_right);
  free(my_rules->mkey_turn);
  free(my_rules->mkey_drop);
  free(my_rules->mkey_quit);
  free(my_rules->mkey_pause);
  free_tab(tetris.map);
  free_tetri(tetris.actual_tetri);
  free_tetri(tetris.next_tetri);
  free(tetris.t);
  i = -1;
  while (shape_list[++i].name != NULL)
    {
      free_tab(shape_list[i].matrix);
      free(shape_list[i].name);
    }
}

int		main(int ac, char **av)
{
  t_game_rules	my_rules;
  t_tetrimino	*shape_list;
  t_tetris	tetris;
  int		i;

  i = 0;
  while (av[++i])
    if (!my_strcmp("--help", av[i]))
      return (help(0, av[0]));
  if (get_gamerules(&my_rules, av, ac) == 84)
    return (84);
  if (get_shape(&shape_list, &my_rules) == 84)
    return (84);
  if (my_rules.debug == 1)
    debug_mode(shape_list, &my_rules);
  tetris.my_rules = &my_rules;
  if (setmap(&tetris) == -1)
    return (84);
  tetris.status = 1;
  tetris.score = 0;
  the_game(&tetris, shape_list);
  endwin();
  my_free_rule(&my_rules, tetris, shape_list);
  free(shape_list);
  return (0);
}
