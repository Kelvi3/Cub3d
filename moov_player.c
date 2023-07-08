#include "MLX42/include/MLX42/MLX42.h"
#include	"cub3D.h"

static void	moov_up_and_down(t_map *img, double movespeed)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_W))
	{
		if (img->map.map[(int)(img->pos_x + img->dir_x)][(int)img->pos_x] != '1')
			img->pos_x += img->dir_x * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + img->dir_y)] != '1')
			img->pos_y += img->dir_y * movespeed;
	}
	if (mlx_is_key_down(img->mlx, MLX_KEY_S))
	{
		if (img->map.map[(int)(img->pos_x - img->dir_x)][(int)img->pos_y] != '1')
			img->pos_x -= img->dir_x * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y - img->dir_y)] != '1')
			img->pos_y -= img->dir_y * movespeed;
	}
}

static void	moov_left_and_right(t_map *img, double movespeed)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_A))
	{
		if (img->map.map[(int)(img->pos_x + img->dir_y)][(int)(img->pos_y)] \
				!= '1')
			img->pos_x += img->dir_y * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + (-img->dir_x))]
				!= '1')
			img->pos_y += (-img->dir_x) * movespeed;
	}
	if (mlx_is_key_down(img->mlx, MLX_KEY_D))
	{
		if (img->map.map[(int)(img->pos_x + (-img->dir_y))][(int)img->pos_y] \
				!= '1')
			img->pos_x += (-img->dir_y) * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + img->dir_x)] != '1')
			img->pos_y += img->dir_x * movespeed;
	}
}

static void	turn_camera(t_map *img)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = 0.2;
	if (mlx_is_key_down(img->mlx, MLX_KEY_LEFT))
	{
		oldDirX = img->dir_x;
		img->dir_x = img->dir_x * cos(-rotSpeed) - img->dir_y * sin(-rotSpeed);
		img->dir_y = oldDirX * sin(-rotSpeed) + img->dir_y * cos(-rotSpeed);
		oldPlaneX = img->plane_x;
		img->plane_x = img->plane_x * cos(-rotSpeed) - img->plane_y * sin(-rotSpeed);
		img->plane_y = oldPlaneX * sin(-rotSpeed) + img->plane_y * cos(-rotSpeed);
	}
	if (mlx_is_key_down(img->mlx, MLX_KEY_RIGHT))
	{
		oldDirX = img->dir_x;
		img->dir_x = img->dir_x * cos(rotSpeed) - img->dir_y * sin(rotSpeed);
		img->dir_y = oldDirX * sin(rotSpeed) + img->dir_y * cos(rotSpeed);
		oldPlaneX = img->plane_x;
		img->plane_x = img->plane_x * cos(rotSpeed) - img->plane_y * sin(rotSpeed);
		img->plane_y = oldPlaneX * sin(rotSpeed) + img->plane_y * cos(rotSpeed);
	}
}

void	moov_player(void *param)
{
	double	movespeed;
	t_map	*img;
	//t_cast	cast;

	img = (t_map *)param;
	movespeed = 0.3;
	moov_up_and_down(img, movespeed);
	moov_left_and_right(img, movespeed);
	turn_camera(img);
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
	{
		mlx_terminate(img->mlx);
		return ;
	}
	*img = raycasting(img->map, *img, (*img).cast);
}
