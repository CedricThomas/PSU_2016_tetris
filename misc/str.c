/*
** str.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Feb 22 13:45:37 2017 
** Last update Wed Feb 22 21:23:03 2017 
*/
#include <stdlib.h>
#include "my.h"
#include "tetris.h"
#include "get_next_line.h"

int     is_only_composed_of(char *str1, char *str2)
{
  int   i;

  i = -1;
  if (str1 == NULL || str2 == NULL)
    return (0);
  while (str1[++i])
    if (!is_in(str1[i], str2))
      return (0);
  return (1);
}

char	**realloc_tab(char **tab, int size)
{
  int	i;
  char	**realloc_tab;

  i = -1;
  if ((realloc_tab = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  while (tab[++i])
    realloc_tab[i] = tab[i];
  free(tab);
  return (realloc_tab);
}

char	**fd_to_tab(int fd, int h)
{
  char	*line;
  char	**tab;
  int	compteur;

  compteur = 0;
  if ((tab = malloc(sizeof(char *) * (h + 1))) == NULL)
    exit(84);
  while ((line = get_next_line(fd)) != NULL)
    {
      tab[compteur] = NULL;
      if (compteur == h)
	tab = realloc_tab(tab, ++h);
      tab[compteur] = line;
      compteur += 1;
    }
  tab[compteur] = NULL;
  return (tab);
}
