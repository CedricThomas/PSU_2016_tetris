/*
** values.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Mar  8 10:05:36 2017 
** Last update Fri Mar 10 12:37:08 2017 Cédric Thomas
*/
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

static int	fill_keys(t_game_rules *my_rules, int test)
{
  if (my_rules->mkey_left == NULL)
    if ((my_rules->mkey_left =
	 my_strdup(tigetstr(test ? "kcub1" : "kcub1"))) == NULL)
      return (84);
  if (my_rules->mkey_right == NULL)
    if ((my_rules->mkey_right =
	 my_strdup(tigetstr(test ? "kcuf1" : "kcuf1"))) == NULL)
      return (84);
  if (my_rules->mkey_turn == NULL)
    if ((my_rules->mkey_turn =
	 my_strdup(tigetstr(test ? "kcuu1" : "kcuu1"))) == NULL)
      return (84);
  if (my_rules->mkey_drop == NULL)
    if ((my_rules->mkey_drop =
	 my_strdup(tigetstr(test ? "kcud1" : "kcud1"))) == NULL)
      return (84);
  if (my_rules->mkey_quit == NULL)
    if ((my_rules->mkey_quit = my_strdup("q")) == NULL)
      return (84);
  if (my_rules->mkey_pause == NULL)
    if ((my_rules->mkey_pause = my_strdup(" ")) == NULL)
      return (84);
  return (0);
}

int	fill_default_gamerules(t_game_rules *my_rules)
{
  char	test;

  setupterm(NULL, 0, NULL);
  test = (tigetstr("smkx") == NULL);
  if (fill_keys(my_rules, test) == 84)
    return (84);
  endwin();
  if (my_rules->level == -1)
    my_rules->level = 1;
  if (my_rules->map.x == -1 && my_rules->map.y == -1)
    my_rules->map = myvector2i(10, 20);
  return (0);
}

int	set_default_gamerules(t_game_rules *my_rules)
{
  my_rules->level = -1;
  my_rules->mkey_left = NULL;
  my_rules->mkey_right = NULL;
  my_rules->mkey_turn = NULL;
  my_rules->mkey_drop = NULL;
  my_rules->mkey_quit = NULL;
  my_rules->mkey_pause = NULL;
  my_rules->map = myvector2i(-1, -1);
  my_rules->next = FALSE;
  my_rules->debug = FALSE;
  return (0);
}
