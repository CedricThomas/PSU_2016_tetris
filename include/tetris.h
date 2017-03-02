/*
** tetris.h for tetris in /home/cedric/delivery/PSU/PSU_2016_tetris
**
** Made by
** Login   <cedric.thomas@epitech.eu>
**
** Started on  Mon Feb 20 20:44:55 2017
** Last update Thu Mar  2 15:37:57 2017 
*/

#ifndef TETRIS_H_
# define TETRIS_H_

# include <sys/types.h>
# include <dirent.h>
# include <termio.h>

# define TRUE	1
# define FALSE	0

# define FOLDER_TETRIS	"tetriminoes"
# define NB_COLORS	9
# define SCORE_CUBE	10
# define LINE_TO_UP	4
# define CYCLE_MAX	10000

# define ARGS_VALUES	10
# define ARGS_TYPE	4
# define INPUT_NB	6

# define PNULL		0
# define PVALUE		1
# define PVECTOR	2
# define PKEY		3
# define PBOOLEAN	4

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

typedef struct		s_parse
{
  char			*short_name;
  char			*long_name;
  void			*value;
  int			type;
}			t_parse;

typedef struct		s_game_rules
{
  char			*mkey_left;
  char			*mkey_right;
  char			*mkey_turn;
  char			*mkey_drop;
  char			*mkey_quit;
  char			*mkey_pause;
  int			level;
  t_vector2i		map;
  int			next;
  int			debug;
}			t_game_rules;

/*
** status : 0 in game | 1 in pause | 2 quit
*/

typedef struct		s_tetris
{
  char			**map;
  t_game_rules		*my_rules;
  int			status;
  int			cycle;
  int			score;
  int			line;
  t_time		*t;
  t_tetrimino		*actual_tetri;
  t_tetrimino		*next_tetri;
  t_vector2i		pos_map;
  t_vector2i		term_size;
}			t_tetris;

typedef struct		s_input
{
  char			**sequence;
  void			(**fct)(t_tetris *);
  char			*input;
}			t_input;

int	help(int jump, char *name);

/*
** DEBUG_MODE/debug.c
*/

int	debug_mode(t_tetrimino *form_list, t_game_rules *my_rules);

/*
** GAME
*/

/*
**the_game.c
*/

int	the_game(t_tetris *tetris, t_tetrimino *shape_list);

/*
**time.c
*/

int	set_time(t_time *t);
int	find_time(t_time *t);
int	interpret_time(t_time *t, t_vector2i pos);

/*
**term.c
*/

int	my_set_term(struct termio *termios);
int	my_reset_term(struct termio *termio);

/*
**misc.c
*/
int	setmap(t_tetris *tetris);
int	del_full_lines(t_tetris *tetris);
void	free_tetri(t_tetrimino *tet);
int	auto_drop(t_tetris *tetris);

/*
**events.c
*/
void	my_pause(t_tetris *tetris);
void    my_turn(t_tetris *tetris);
void    my_quit(t_tetris *tetris);
void    my_left(t_tetris *tetris);
void    my_right(t_tetris *tetris);
void    my_drop(t_tetris *tetris);

/*
**inputs.c
*/
int	set_input(t_input *my_inputs, t_tetris *tetris);
int	reset_input(t_input *my_inputs);
int	try_input(t_input *my_inputs, t_tetris *tetris);

/*
**print.c
*/
int	print_game(t_tetris *tetris, t_tetrimino *shape_list);

/*
**tetra.c
*/
int		gen_tetri(t_tetris *tetris, t_tetrimino *shape_list);
int		try_tetri(t_tetris *tetris, t_tetrimino *tetri);
int             add_to_map(t_tetris *tetris, t_tetrimino *tetri);
t_tetrimino	*my_dup_tetri(t_tetrimino tet);
int		auto_drop(t_tetris *tetris);

/*
**PARSE
*/

int     match(char *s1, char *s2);

/*
**PARSE/ARGS
*/

/*
**args.c
*/

int	get_gamerules(t_game_rules *myrules, char **args, int ac);

/*
**prepare.c
*/

int	prepare_long(t_parse *parse,
		     char **args,
		     int *i,
		     int (*fct[ARGS_TYPE])(t_parse *parse, char *value));
int	prepare_short(t_parse *parse,
		      char **args,
		      int *i,
		      int (*fct[ARGS_TYPE])(t_parse *parse, char *value));
int	gamerules_fct(int (*fct[ARGS_TYPE])(t_parse *parse, char *value));

/*
**type.c
*/

int     parse_boolean(t_parse *parse, char *value);
int     parse_value(t_parse *parse, char *value);
int     parse_key(t_parse *parse, char *value);
int     parse_vector(t_parse *parse, char *value);

/*
**PARSE/TETRIMINO
*/

/*
**tetris.c
*/

int		get_shape(t_tetrimino **form_list);

/*
**shape.c
*/

int		fill_shape(int fd, char **header,
			   int index, t_tetrimino **shape_list);

/*
**misc.c
*/

DIR		*my_opendir(char *path);
int		my_open(char *path);
char		*cut_ext(char *file, char *ext);
int		my_len_sum(char **mtab);
int		clean_gnl(int fd);

/*
**sort.c
*/

void		sort_tetri(t_tetrimino **shape_list);
int		check_color(t_tetrimino **shape_list);

/*
**MATH
*/

/*
**vector.c
*/

t_vector2i	myvector2i(int x, int y);
t_vector2i	addvec(t_vector2i vec1, t_vector2i vec2);

/*
**matrix.c
*/

int		rrotate_matrix(t_matrix *matrix);
int		create_matrix(int x, int y, t_matrix *);
int		show_tetri(t_matrix *matrix);

/*
**MISC
*/

/*
**nbr.c
*/

int	is_an_int(char *str);

/*
**str.c
*/

char	**fd_to_tab(int fd, int h);
int	is_only_composed_of(char *str1, char *str2);
char	**realloc_tab(char **mtab, int size);

#endif /* !TETRIS_H_ */
