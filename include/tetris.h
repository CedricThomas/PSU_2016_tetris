/*
** tetris.h for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Feb 20 20:44:55 2017 
** Last update Wed Feb 22 00:59:51 2017 
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

/*
**SIMPLE STRUCT
*/

typedef struct		s_vector2i
{
  int			x;
  int			y;
}			t_vector2i;

typedef struct		s_matrix
{
  char			*name;
  int			**matrix;
  int			x;
  int			y;
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

int	get_form(t_tetrimino **form_list);

/*
**MATH
*/

t_vector2i	myvector2i(int x, int y);

/*
**MISC
*/

int	is_an_int(char *str);

#endif /* !TETRIS_H_ */
