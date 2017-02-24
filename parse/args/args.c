/*
** args.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 22:23:37 2017
** Last update Fri Feb 24 19:05:17 2017 Maxime Jenny
*/
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
    {"-w", "–-without-next", NULL, 0},
    {"-d", "--debug", NULL, 0}
  };

static void	link_pointers(t_game_rules *my_rules)
{
  myparse[0].value = &(my_rules->level);
  myparse[0].type = PVALUE;
  myparse[1].value = &(my_rules->key_Left);
  myparse[1].type = PKEY;
  myparse[2].value = &(my_rules->key_Right);
  myparse[2].type = PKEY;
  myparse[3].value = &(my_rules->key_Turn);
  myparse[3].type = PKEY;
  myparse[4].value = &(my_rules->key_Drop);
  myparse[4].type = PKEY;
  myparse[5].value = &(my_rules->key_Quit);
  myparse[5].type = PKEY;
  myparse[6].value = &(my_rules->key_Pause);
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
      help(1);
    }
  return (exitval ? 1 : 0);
}

static int	get_default_gamerules(t_game_rules *my_rules)
{
  my_rules->level = 1;
  if ((my_rules->key_Left = my_strdup("^[[D")) == NULL)
    return (84);
  if ((my_rules->key_Right = my_strdup("^[[C")) == NULL)
    return (84);
  if ((my_rules->key_Turn = my_strdup("^[[A")) == NULL)
    return (84);
  if ((my_rules->key_Drop = my_strdup("^[[B")) == NULL)
    return (84);
  if ((my_rules->key_Quit = my_strdup("Q")) == NULL)
    return (84);
  if ((my_rules->key_Pause = my_strdup(" ")) == NULL)
    return (84);
  my_rules->map = myvector2i(10, 20);
  my_rules->next = FALSE;
  my_rules->debug = FALSE;
  return (0);
}

static int	check_new_rules(t_game_rules *my_rules)
{
  if (my_rules->level <= 0 || my_rules->level > 10)
    {
      my_puterror("Error : level must be between 1 and 10\n");
      return (84);
    }
  if (my_rules->map.x <= 0 || my_rules->map.y <= 0)
    return (84);
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
