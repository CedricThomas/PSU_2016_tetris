/*
** tetra.c for tetra in /home/Maxime/delivery/PSU/PSU_2016_tetris/game/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu@epitech.eu>
**
** Started on  Mon Feb 27 22:05:39 2017 Maxime Jenny
** Last update Tue Feb 28 13:22:18 2017 Maxime Jenny
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"
#include "my.h"

int		roll_a_tetra(t_tetrimino *shape_list, t_tetris *tetris,
			     t_tetrimino *tetra)
{
  int		i;
  int		tmp;
  int		good;

  i = 0;
  good = 0;
  srand(getpid() * time(NULL) * getpid() * 9 * time(NULL));
  while (shape_list[++i].name != NULL);
  while (!good)
    {
      tmp = rand() % i;
      if (shape_list[tmp].valid == 1)
	continue;
      good = 1;
    }
  tetra = &shape_list[tmp];
}

int		tetra(t_tetris *tetris, t_tetrimino *shape_list,
		      struct winsize size)
{
  if (tetris->actual_tetra == NULL)
    {
      tetris->pos_tetra.x = tetris->my_rules->map.x / 2 + size.ws_col / 2;
      tetris->pos_tetra.y = size.ws_row / 2 - tetris->my_rules->map.y / 2;
      if (tetris->next_tetra != NULL)
	{
	  tetris->actual_tetra = tetris->next_tetra;
	  tetris->next_tetra = NULL;
	}
      else
	roll_a_tetra(shape_list, tetris, tetris->actual_tetra);
    }
  if (tetris->next_tetra == NULL)
    roll_a_tetra(shape_list, tetris, tetris->next_tetra);
}
