# ifndef  CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_data t_data;
typedef struct s_cast t_cast;

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

typedef struct s_cast
{
	int color;
	int x;
	int y;
	int texWidth;
	int texHeight;
	int texNum;
	int texY;
	double step;
	double texPos;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit; // was there a wall hit?
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX;
	int texX;
} t_cast;

typedef struct	s_map
{
	mlx_t	*mlx;
	mlx_image_t *image;
	mlx_texture_t *texture;
	void	*mlx_win;
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
	t_cast	cast;
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
t_map	raycasting(t_data map, t_map img, t_cast cast);
void	my_mlx_pixel_put(t_map *data, int x, int y, int color);

void	calculate_step_and_initial_sidedist(t_cast *cast, t_map img);
void	calculate_pos_and_dir(t_cast *cast, t_map img);
void	calculate_lowest_and_highest_pixel(t_cast *cast);

/* moov_player */

void	moov_player(void *param);
void	moov_camera(mlx_key_data_t keydata, void *param);
#endif
