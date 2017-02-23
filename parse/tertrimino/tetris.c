/*
** tetris.c for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris/parse/tertrimino
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Feb 21 20:54:39 2017 
** Last update Wed Feb 22 22:09:57 2017 
*/
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include "my_printf.h"
#include "tetris.h"
#include "get_next_line.h"

static int	check_header(char **header, char *line)
{
  int		i;

  i = -1;
  while (header[++i])
    if (is_an_int(header[i]))
      return (84);
  if (i != 3)
    return (84);
  if (my_strlen(line) != my_len_sum(header) + 2)
    return (84);
  return (0);
}

static int	get_shape_from_file(int index, char *path,
				    char *name, t_tetrimino **shape_list)
{
  int		i;
  int		fd;
  char		**header;
  char		*s;

  (*shape_list)[index].valid = 0;
  (*shape_list)[index].name = cut_ext(name, ".tetrimino");
  if ((fd = my_open(path)) == 84)
    exit(84);
  if ((s = get_next_line(fd)) == NULL)
    return (84);
  if ((header = my_split(s, ' ')) == NULL)
    exit(84);
  if (check_header(header, s))
    return (clean_gnl(fd));
  if (fill_shape(fd, header, index, shape_list))
    return (clean_gnl(fd));
  free(s);
  free_tab(header);
  (*shape_list)[index].valid = 1;
  clean_gnl(fd);
  return (0);
}

static int	fill_list(t_tetrimino **shape_list, char *path)
{
  DIR		*my_folder;
  t_dirent	*dp;
  t_stat	my_stat;
  char		*exec_path;
  int		index;

  index = 0;
  if ((my_folder = my_opendir(path)) == NULL)
    return (84);
  while ((dp = readdir(my_folder)) != NULL)
    if (match(dp->d_name, "*.tetrimino"))
      {
	if ((exec_path = my_strcatdup(path, dp->d_name, 0)) == NULL)
	  return (84);
	if (lstat(exec_path, &my_stat) == -1)
	  return (84);
	if (S_ISREG(my_stat.st_mode))
	  {
	    get_shape_from_file(index, exec_path, dp->d_name, shape_list);
	    index += 1;
	  }
	free(exec_path);
      }
  closedir(my_folder);
  return (0);
}

static int	get_shape_nbr(t_tetrimino **shape_list, char *path, int *size)
{
  char		*exec_path;
  DIR		*my_folder;
  t_dirent	*dp;
  t_stat	my_stat;

  *size = 0;
  if ((my_folder = my_opendir(path)) == NULL)
    return (84);
  while ((dp = readdir(my_folder)) != NULL)
    if (match(dp->d_name, "*.tetrimino"))
      {
	if ((exec_path = my_strcatdup(path, dp->d_name, 0)) == NULL)
	  return (84);
	if (lstat(exec_path, &my_stat) == -1)
	  return (84);
	if (S_ISREG(my_stat.st_mode))
	  *size += 1;
	free(exec_path);
      }
  if ((*shape_list = malloc(sizeof(t_tetrimino) * (*size + 1))) == NULL)
    return (84);
  (*shape_list)[*size].name = NULL;
  (*shape_list)[*size].matrix = NULL;
  closedir(my_folder);
  return (0);
}

int	get_shape(t_tetrimino **shape_list)
{
  char	*path;
  int	size;

  if ((path = my_strdup(FOLDER_TETRIS)) == NULL)
    return (84);
  if (path[my_strlen(path) - 1] != '/')
    if ((path = my_strcatdup(path, "/", 1)) == NULL)
      return (84);
  if (get_shape_nbr(shape_list, path, &size) == 84)
    return (84);
  if (fill_list(shape_list, path))
    return (84);
  free(path);
}
