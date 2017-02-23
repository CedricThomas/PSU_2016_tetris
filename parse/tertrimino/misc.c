/*
** open.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Feb 22 10:03:46 2017 
** Last update Wed Feb 22 15:28:22 2017 
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "my.h"
#include "tetris.h"

int	clean_gnl(int fd)
{
  char	*s;

  while ((s = get_next_line(fd)) != NULL)
    free(s);
  close(fd);
}

int	my_len_sum(char **tab)
{
  int	i;
  int	sum;

  i = -1;
  sum = 0;
  while (tab[++i])
    sum += my_strlen(tab[i]);
  return (sum);
}

DIR	*my_opendir(char *path)
{
  DIR	*my_folder;

  if ((my_folder = opendir(path)) == NULL)
    {
      my_puterror(path);
      my_puterror(": cannot open directory\n");
      return (NULL);
    }
  return (my_folder);
}

int	my_open(char *path)
{
  int	fd;

  if ((fd = open(path, O_RDONLY)) == -1)
    {
      my_puterror(path);
      my_puterror(": cannot open file\n");
      return (84);
    }
  return (fd);
}

char	*cut_ext(char *file, char *ext)
{
  int	file_i;
  int	ext_i;
  char	*name;

  ext_i = my_strlen(ext) - 1;
  file_i = my_strlen(file) - 1;
  while (ext[ext_i] == file[file_i] && ext_i > 0 && file_i > 0)
    {
      file_i--;
      ext_i--;
    }
  if ((name = malloc(sizeof(char) * (file_i + 1))) == NULL)
    return (NULL);
  name = my_strncpy(name, file, file_i + 1);
  name[file_i] = 0;
  return (name);
}
