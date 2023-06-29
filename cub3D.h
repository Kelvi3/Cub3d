# ifndef  CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

typedef struct s_data t_data;

typedef struct s_data
{
	char	**map;
	char	**cub;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*color_f;
	char	*color_c;
	int		colorf[3];
	int		colorc[3];

}				t_data;

typedef struct	s_map
{
	void	*mlx_win;
	void	*mlx;
	char	*addr;
	void	*img;
	void	*floor;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	t_data	map;
}				t_map;

		/*	PARSE	*/
char	*get_next_line(int fd);
int		parse(t_data *map);
int		copy_map(t_data *map);
int		check_char_in_map(t_data *map);
int		check_map(t_data *map);
int		check_color(char *color);
int		add_color_in_tab_f(t_data *map);
int		add_color_in_tab_c(t_data *map);
int		check_len_int_tab(int tab[3]);
int		size_file_cub(char **argv);
int		count_size_map(t_data *map, int i);
int		check_path(t_data *map);
int		not_player(char c);
int		check_char_player_egal(char c);
void	init_value_data(t_data *map);
void	add_all_cube(char **argv, t_data *map);
void	check_extension(char *str, char *ext);
void	add_path_texture(t_data *map);
void	add_color(t_data *map);
void	pass_space(char *str, int *i);

		/*	UTILS	*/
void	free_tab(char **tab);
void	free_all(t_data *map);

/* RAYCASTING */
t_map	raycasting(t_data map, t_map img);
t_map	floorcasting(t_data map, t_map img);
void	my_mlx_pixel_put(t_map *data, int x, int y, int color);

/* moov_player */

int	moov_player(int keycode, t_map *img);

#endif
