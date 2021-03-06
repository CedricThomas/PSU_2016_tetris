/*
** type.c for type in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/args
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Feb 21 15:00:13 2017 
** Last update Wed Mar 15 17:50:17 2017 
*/
#include <curses.h>
#include <stdlib.h>
#include "my.h"
#include "tetris.h"

int	invalid_parse(t_parse *parse, char *str)
{
  my_puterror("Error : ");
  my_puterror(str);
  my_puterror(" for ");
  if (parse->short_name != NULL)
    {
      my_puterror(parse->short_name);
      my_puterror("/");
    }
  my_puterror(parse->long_name);
  my_puterror("\n");
  return (84);
}

int	parse_boolean(t_parse *parse, char *value)
{
  int	*casted;

  if (value == NULL)
    value = NULL;
  else
    value = NULL;
  casted = (int *)parse->value;
  *casted = 1;
  return (0);
}

int	parse_value(t_parse *parse, char *value)
{
  int	*casted;

  casted = (int *)parse->value;
  if (*casted != -1)
    return (invalid_parse(parse, "the value as already been set"));
  if (is_an_int(value))
   return (invalid_parse(parse, "invalid value"));
  *casted = my_getnbr(value);
  if (*casted <= 0 || *casted > 10)
    return (invalid_parse(parse, "the value must be between 0 and 10"));
  return (0);
}

int	parse_key(t_parse *parse, char *value)
{
  char	**casted;

  casted = (char **)parse->value;
  if (*casted != NULL)
    return (invalid_parse(parse, "the value as already been set"));
  if (my_strlen(value) <= 0)
    return (invalid_parse(parse, "invalid value"));
  if ((*casted = my_strdup(value)) == NULL)
    return (84);
  return (0);
}

int		parse_vector(t_parse *parse, char *value)
{
  t_vector2i	*casted;
  char		**tabvec;
  int		i;

  i = -1;
  if ((tabvec = my_split (value, ',')) == NULL)
    return (84);
  while (tabvec[++i]);
  if (i != 2)
    return (invalid_parse(parse, "invalid vector"));
  if (my_strlen(tabvec[0]) + my_strlen(tabvec[1]) + 1 != my_strlen(value))
    return (invalid_parse(parse, "invalid vector"));
  if (is_an_int(tabvec[0]) || is_an_int(tabvec[1]))
    return (invalid_parse(parse, "invalid vector value(s)"));
  casted = (t_vector2i *)parse->value;
  if (casted->x != -1 || casted->y != -1)
    {
      free_tab(tabvec);
      return (invalid_parse(parse, "the value as already been set"));
    }
  *casted = myvector2i(my_getnbr(tabvec[1]), my_getnbr(tabvec[0]));
  free_tab(tabvec);
  if (casted->x <= 0 || casted->y <= 0)
    return (invalid_parse(parse, "the values must be positives"));
  return (0);
}
