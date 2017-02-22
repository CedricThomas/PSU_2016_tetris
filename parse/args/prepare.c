/*
** long.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Feb 21 11:29:08 2017 
** Last update Wed Feb 22 09:18:44 2017 
*/
#include <stdlib.h>
#include "tetris.h"
#include "my.h"

int	gamerules_fct(int (*fct[ARGS_TYPE])(t_parse *parse, char *value))
{
  fct[PVALUE - 1] = &parse_value;
  fct[PVECTOR - 1] = &parse_vector;
  fct[PKEY- 1] = &parse_key;
  fct[PBOOLEAN - 1] = &parse_boolean;
}

int	prepare_long(t_parse *parse,
		     char **args, int *i,
		     int (*fct[ARGS_TYPE])(t_parse *parse, char *value))
{
  char	*args_value;
  char	*key;

  key = parse->long_name;
  if (parse->type == PBOOLEAN && !my_strcmp(args[*i], parse->long_name))
    args_value = NULL;
  else if (args[*i][my_strlen(key)] == '=')
    args_value = args[*i] + my_strlen(key) + 1;
  else
    return (1);
  return (fct[parse->type - 1](parse, args_value));
}

int	prepare_short(t_parse *parse,
		      char **args, int *i,
		      int (*fct[ARGS_TYPE])(t_parse *parse, char *value))
{
  char	*args_value;

  if (parse->type == PBOOLEAN)
    args_value = NULL;
  else if (args[*i + 1] != NULL)
    {
      args_value = args[*i + 1];
      (*i)++;
    }
  else
    {
      my_puterror("Error : missing argument\n");
      return (1);
    }
  return (fct[parse->type - 1](parse, args_value));
}
