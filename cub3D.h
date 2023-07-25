/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:11:51 by tcazenav          #+#    #+#             */
/*   Updated: 2023/07/25 09:12:28 by tcazenav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CUB3D_H
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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_data	t_data;
typedef struct s_cast	t_cast;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

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
	int		color;
	int		x;
	int		y;
	int		tex_width;
	int		tex_height;
	int		tex_y;
	int		tex_x;
	int		map_x;
	int		map_y;
	double	step;
	double	tex_pos;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}				t_cast;

typedef struct s_map
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	mlx_texture_t	*texture_n;
	mlx_texture_t	*texture_s;
	mlx_texture_t	*texture_e;
	mlx_texture_t	*texture_w;
	void			*mlx_win;
	char			*addr;
	void			*img;
	void			*floor;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	t_data			map;
	t_cast			cast;
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
void	init_value_data(int argc, t_data *map);
void	add_all_cube(char **argv, t_data *map);
void	check_extension(char *str, char *ext);
void	add_path_texture(t_data *map);
void	add_color(t_data *map);
void	pass_space(char *str, int *i);

		/*	UTILS	*/
void	free_tab(char **tab);
void	free_all(t_data *map);
void	end_program(void *param);

/* RAYCASTING */
t_map	raycasting(t_data map, t_map img, t_cast cast);
void	my_mlx_pixel_put(t_map *data, int x, int y, int color);
void	floor_wall_ceiling(t_map img, t_cast *cast, t_data map);

void	calculate_step_and_initial_sidedist(t_cast *cast, t_map img);
void	calculate_pos_and_dir(t_cast *cast, t_map img);
void	calculate_lowest_and_highest_pixel(t_cast *cast);
void	calculate_distance_perpendicular_ray(t_cast *cast);

/* moov_player */

void	moov_player(void *param);
void	moov_camera(mlx_key_data_t keydata, void *param);
#endif
