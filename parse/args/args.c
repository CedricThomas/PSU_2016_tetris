/*
** args.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 22:23:37 2017
** Last update Thu Mar 16 12:04:55 2017 Cédric Thomas
*/
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf.h"
#include "tetris.h"

static t_parse	g_myparse[ARGS_VALUES] =
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
  g_myparse[0].value = &(my_rules->level);
  g_myparse[0].type = PVALUE;
  g_myparse[1].value = &(my_rules->mkey_left);
  g_myparse[1].type = PKEY;
  g_myparse[2].value = &(my_rules->mkey_right);
  g_myparse[2].type = PKEY;
  g_myparse[3].value = &(my_rules->mkey_turn);
  g_myparse[3].type = PKEY;
  g_myparse[4].value = &(my_rules->mkey_drop);
  g_myparse[4].type = PKEY;
  g_myparse[5].value = &(my_rules->mkey_quit);
  g_myparse[5].type = PKEY;
  g_myparse[6].value = &(my_rules->mkey_pause);
  g_myparse[6].type = PKEY;
  g_myparse[7].value = &(my_rules->map);
  g_myparse[7].type = PVECTOR;
  g_myparse[8].value = &(my_rules->next);
  g_myparse[8].type = PBOOLEAN;
  g_myparse[9].value = &(my_rules->debug);
  g_myparse[9].type = PBOOLEAN;
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
      while (++j < ARGS_VALUES && exitval == -1)
	if (g_myparse[j].short_name != NULL &&
	    !my_strcmp(g_myparse[j].short_name, args[i]))
	  exitval = prepare_short(&g_myparse[j], args, &i, fct);
	else if (!my_strncmp(g_myparse[j].long_name, args[i],
			     my_strlen(g_myparse[j].long_name)))
	  exitval = prepare_long(&g_myparse[j], args, &i, fct);
    }
  if (exitval)
    {
      my_puterror(args[i - 1]);
      my_puterror(" is an invalid argument\n");
      help(1, args[0]);
    }
  return (exitval ? 1 : 0);
}

static int	check_new_rules()
{
  int		j;
  int		i;

  i = 0;
  while (++i < 7)
    {
      j = 0;
      while (++j < 7)
	if (i != j && !my_strncmp(*((char **)g_myparse[i].value),
				  *((char **)g_myparse[j].value),
				  my_strlen(*((char **)g_myparse[i].value))))
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

  if (set_default_gamerules(my_rules) == 84)
    return (84);
  link_pointers(my_rules);
  if (ac > 1)
    {
      gamerules_fct(fct);
      if (cmp_args(args, ac, fct))
	return (84);
    }
  if (fill_default_gamerules(my_rules) == 84)
    return (84);
  if (check_new_rules())
    return (84);
  my_rules->next = (!my_rules->next ? 1 : 0);
  return (0);
}
