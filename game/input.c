/*
** input.c for input in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sun Feb 26 13:32:53 2017
** Last update Sun Mar 12 15:03:32 2017 
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "tetris.h"

int		set_input(t_input *my_inputs, t_tetris *tetris)
{
  t_game_rules	*rules;

  rules = tetris->my_rules;
  if ((my_inputs->sequence = malloc(sizeof(char *) * INPUT_NB)) == NULL)
    return (84);
  if ((my_inputs->fct = malloc(sizeof(my_inputs->fct) * INPUT_NB)) == NULL)
    return (84);
  my_inputs->input = NULL;
  my_inputs->sequence[0] = rules->mkey_left;
  my_inputs->sequence[1] = rules->mkey_right;
  my_inputs->sequence[2] = rules->mkey_turn;
  my_inputs->sequence[3] = rules->mkey_drop;
  my_inputs->sequence[4] = rules->mkey_quit;
  my_inputs->sequence[5] = rules->mkey_pause;
  my_inputs->fct[0] = &my_left;
  my_inputs->fct[1] = &my_right;
  my_inputs->fct[2] = &my_turn;
  my_inputs->fct[3] = &my_drop;
  my_inputs->fct[4] = &my_quit;
  my_inputs->fct[5] = &my_pause;
  return (0);
}

static void	free_intput(t_input *my_inputs, int match)

{  if (!match)
    {
      free(my_inputs->input);
      my_inputs->input = NULL;
    }
}

int	try_input(t_input *my_inputs, t_tetris *tetris)
{
  char	buff[2];
  int	match;
  int	i;

  i = -1;
  if ((match = read(0, buff, 1)) != 0 && match != -1)
    {
      buff[match] = 0;
      if ((my_inputs->input = my_strcatdup(my_inputs->input, buff, 1)) == NULL)
	return (84);
    }
  if (match != -1)
    match = 0;
  while (++i < INPUT_NB && my_inputs->input != NULL && match != -1)
    {
      if (!my_strcmp(my_inputs->sequence[i], my_inputs->input))
	my_inputs->fct[i](tetris);
      else if (!my_strncmp(my_inputs->input, my_inputs->sequence[i],
			   my_strlen(my_inputs->input)))
	match = 1;
    }
  free_intput(my_inputs, match);
  return (0);
}

int	reset_input(t_input *my_inputs)
{
  free(my_inputs->sequence);
  free(my_inputs->fct);
  free(my_inputs->input);
  return (0);
}
