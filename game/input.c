/*
** input.c for input in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Sun Feb 26 13:32:53 2017
** Last update Sun Feb 26 17:08:57 2017
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
  my_inputs->sequence[0] = rules->key_left;
  my_inputs->sequence[1] = rules->key_right;
  my_inputs->sequence[2] = rules->key_turn;
  my_inputs->sequence[3] = rules->key_drop;
  my_inputs->sequence[4] = rules->key_quit;
  my_inputs->sequence[5] = rules->key_pause;
  my_inputs->fct[0] = &my_left;
  my_inputs->fct[1] = &my_right;
  my_inputs->fct[2] = &my_turn;
  my_inputs->fct[3] = &my_drop;
  my_inputs->fct[4] = &my_quit;
  my_inputs->fct[5] = &my_pause;
}

int	try_input(t_input *my_inputs, t_tetris *tetris)
{
  char	buffer[1000];
  int	match;
  int	i;

  i = -1;
  if ((match = read(0, buffer, 999)) != 0)
    {
      buffer[match] = 0;
      my_inputs->input = my_strcatdup(my_inputs->input, buffer, 1);
    }
  match = 0;
  while (++i < INPUT_NB && my_inputs->input != NULL)
    {
      if (!my_strcmp(my_inputs->sequence[i], my_inputs->input))
	my_inputs->fct[i](tetris);
      else if (!my_strncmp(my_inputs->input, my_inputs->sequence[i],
			   my_strlen(my_inputs->input)))
	match = 1;
    }
  if (!match)
    {
      free(my_inputs->input);
      my_inputs->input = NULL;
    }
}

int	reset_input(t_input *my_inputs)
{
  free(my_inputs->sequence);
  free(my_inputs->fct);
  free(my_inputs->input);
}
