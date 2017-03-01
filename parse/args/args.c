/*
** args.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 22:23:37 2017
** Last update Tue Feb 28 22:17:57 2017 
*/
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"
#include "tetris.h"

static t_parse	myparse[ARGS_VALUES] =
  {
    {"-l", "--level", NULL, 0},
    {"-kl", "--key-left", NULL, 0},
    {"-kr", "--key-right", NULL, 0},
    {"-kt", "--key-turn", NULL, 0},
    {"-kd", "--key-drop", NULL, 0},
    {"-kq", "--key-quit", NULL, 0},
    {"-kp", "--key-pause", NULL, 0},
    {NULL, "--map-size", NULL, 0},
    {"-w", "--without-next", NULL, 0},
    {"-d", "--debug", NULL, 0}
  };

static void	link_pointers(t_game_rules *my_rules)
{
  myparse[0].value = &(my_rules->level);
  myparse[0].type = PVALUE;
  myparse[1].value = &(my_rules->mkey_left);
  myparse[1].type = PKEY;
  myparse[2].value = &(my_rules->mkey_right);
  myparse[2].type = PKEY;
  myparse[3].value = &(my_rules->mkey_turn);
  myparse[3].type = PKEY;
  myparse[4].value = &(my_rules->mkey_drop);
  myparse[4].type = PKEY;
  myparse[5].value = &(my_rules->mkey_quit);
  myparse[5].type = PKEY;
  myparse[6].value = &(my_rules->mkey_pause);
  myparse[6].type = PKEY;
  myparse[7].value = &(my_rules->map);
  myparse[7].type = PVECTOR;
  myparse[8].value = &(my_rules->next);
  myparse[8].type = PBOOLEAN;
  myparse[9].value = &(my_rules->debug);
  myparse[9].type = PBOOLEAN;
}

static int	cmp_args(char **args, int ac,
			 int (*fct[ARGS_TYPE])(t_parse *parse, char *value))
{
  int		i;
  int		j;
  int		exitval;

  i = 0;
  exitval = 0;
  while (++i < ac && !exitval)
    {
      exitval = -1;
      j = -1;
      while (++j < ARGS_VALUES)
	if (myparse[j].short_name != NULL &&
	    !my_strcmp(myparse[j].short_name, args[i]))
	  exitval = prepare_short(&myparse[j], args, &i, fct);
	else if (!my_strncmp(myparse[j].long_name, args[i],
			     my_strlen(myparse[j].long_name)))
	  exitval = prepare_long(&myparse[j], args, &i, fct);
    }
  if (exitval)
    {
      my_puterror(args[i - 1]);
      my_puterror(" is an invalid argument\n");
      help(1, args[0]);
    }
  return (exitval ? 1 : 0);
}

static int	get_default_gamerules(t_game_rules *my_rules)
{
  setupterm(NULL, 0, NULL);
  my_rules->level = 1;
  if ((my_rules->mkey_left = my_strdup(tigetstr("kcub1"))) == NULL)
    return (84);
  if ((my_rules->mkey_right = my_strdup(tigetstr("kcuf1"))) == NULL)
    return (84);
  if ((my_rules->mkey_turn = my_strdup(tigetstr("kcuu1"))) == NULL)
    return (84);
  if ((my_rules->mkey_drop = my_strdup(tigetstr("kcud1"))) == NULL)
    return (84);
  if ((my_rules->mkey_quit = my_strdup("q")) == NULL)
    return (84);
  if ((my_rules->mkey_pause = my_strdup(" ")) == NULL)
    return (84);
  my_rules->map = myvector2i(10, 20);
  my_rules->next = FALSE;
  my_rules->debug = FALSE;
  endwin();
  return (0);
}

static int	check_new_rules(t_game_rules *my_rules)
{
  int		j;
  int		i;

  if (my_rules->level <= 0 || my_rules->level > 10)
    {
      my_puterror("Error : level must be between 1 and 10\n");
      return (84);
    }
  if (my_rules->map.x <= 0 || my_rules->map.y <= 0)
    return (84);
  i = 0;
  while (++i < 7)
    {
      j = 0;
      while (++j < 7)
	if (i != j && !my_strncmp(*((char **)myparse[i].value),
				  *((char **)myparse[j].value),
				  my_strlen(*((char **)myparse[i].value))))
	  {
	    my_puterror("Error : severals sequences start with the same values\n");
	    return (84);
	  }
    }
  return (0);
}

int	get_gamerules(t_game_rules *my_rules, char **args, int ac)
{
  int	(*fct[ARGS_TYPE])(t_parse *parse, char *value);

  if (get_default_gamerules(my_rules) == 84)
    return (84);
  if (ac > 1)
    {
      gamerules_fct(fct);
      link_pointers(my_rules);
      if (cmp_args(args, ac, fct))
	return (84);
      if (check_new_rules(my_rules))
	return (84);
    }
  return (0);
}
