/*
** tetris.h for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 20:44:55 2017
** Last update Wed Feb 22 21:08:22 2017
*/
#ifndef TETRIS_H_
# define TETRIS_H_

# define TRUE	1
# define FALSE	0

# define FOLDER_TETRIS	"tetriminoes"

# define ARGS_VALUES	10
# define ARGS_TYPE	4

# define PNULL		0
# define PVALUE		1
# define PVECTOR	2
# define PKEY		3
# define PBOOLEAN	4

# include <sys/types.h>
# include <dirent.h>

/*
**SIMPLE STRUCT
*/

typedef struct		s_time
{
  unsigned long long	first_time;
  unsigned long long	prec_time;
  unsigned long long	actual_time;
  unsigned long long	time_before_pause;
}			t_time;


typedef struct		s_vector2i
{
  int			x;
  int			y;
}			t_vector2i;

typedef struct		s_matrix
{
  char			**matrix;
  t_vector2i		size;
  int			color;
  int			valid;
  t_vector2i		pos;
  char			*name;
}			t_matrix;

typedef struct stat	t_stat;
typedef struct dirent	t_dirent;
typedef t_matrix	t_tetrimino;
typedef t_matrix	t_board;

/*
**COMPLEX STRUCT
*/

typedef struct		s_parse
{
  char			*short_name;
  char			*long_name;
  void			*value;
  int			type;
}			t_parse;

typedef struct		s_game_rules
{
  int			level;
  char			*key_Left;
  char			*key_Right;
  char			*key_Turn;
  char			*key_Drop;
  char			*key_Quit;
  char			*key_Pause;
  t_vector2i		map;
  int			next;
  int			debug;
}			t_game_rules;

typedef struct		t_tetris
{
  char			**map;
  t_game_rules		*my_rules;
}			t_tetris;

int	help(int jump);


/*
** DEBUG_MODE/debug.c
*/

int	debug_mode(t_tetrimino *form_list, t_game_rules *my_rules);

/*
** GAME
*/

int	the_game(t_tetris *tetris, t_tetrimino *form_list);
int	set_time(t_time *t);
int	find_time(t_time *t);
int	interpret_time(t_time *t);

/*
**PARSE
*/

int     match(char *s1, char *s2);

/*
**PARSE/ARGS
*/

int	get_gamerules(t_game_rules *myrules, char **args, int ac);

int	prepare_long(t_parse *parse,
		     char **args,
		     int *i,
		     int (*fct[ARGS_TYPE])(t_parse *parse, char *value));
int	prepare_short(t_parse *parse,
		      char **args,
		      int *i,
		      int (*fct[ARGS_TYPE])(t_parse *parse, char *value));
int	gamerules_fct(int (*fct[ARGS_TYPE])(t_parse *parse, char *value));

int     parse_boolean(t_parse *parse, char *value);
int     parse_value(t_parse *parse, char *value);
int     parse_key(t_parse *parse, char *value);
int     parse_vector(t_parse *parse, char *value);

/*
**PARSE/TETRIMINO
*/

int		get_shape(t_tetrimino **form_list);

int		fill_shape(int fd, char **header,
			   int index, t_tetrimino **shape_list);

DIR		*my_opendir(char *path);
int		my_open(char *path);
char		*cut_ext(char *file, char *ext);
int		my_len_sum(char **tab);
int		clean_gnl(int fd);

/*
**MATH
*/

t_vector2i	myvector2i(int x, int y);

int		create_matrix(int x, int y, t_matrix *);
int		show_tetri(t_matrix *matrix);

/*
**MISC
*/

int	is_an_int(char *str);

char	**fd_to_tab(int fd, int h);
int	is_only_composed_of(char *str1, char *str2);
char	**realloc_tab(char **tab, int size);


#endif /* !TETRIS_H_ */
