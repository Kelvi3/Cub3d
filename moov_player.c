#include "MLX42/include/MLX42/MLX42.h"
#include	"cub3D.h"

static void	moov_up_and_down(mlx_key_data_t keydata, t_map *img, double movespeed)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX + img->dirX)][(int)img->posY] != '1')
			img->posX += img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirY)] != '1')
			img->posY += img->dirY * movespeed;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX - img->dirX)][(int)img->posY] != '1')
			img->posX -= img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY - img->dirY)] != '1')
			img->posY -= img->dirY * movespeed;
	}
}

static void	moov_left_and_right(mlx_key_data_t keydata, t_map *img, double movespeed)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX + img->dirY)][(int)(img->posY)] != '1')
			img->posX += img->dirY * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + (-img->dirX))] != '1')
			img->posY += (-img->dirX) * movespeed;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX + (-img->dirY))][(int)img->posY] != '1')
			img->posX += (-img->dirY) * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirX)] != '1')
			img->posY += img->dirX * movespeed;
	}
}

static void	turn_camera(mlx_key_data_t keydata, t_map *img, void *param)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = 0.2;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(-rotSpeed) - img->dirY * sin(-rotSpeed);
		img->dirY = oldDirX * sin(-rotSpeed) + img->dirY * cos(-rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(-rotSpeed) - img->planeY * sin(-rotSpeed);
		img->planeY = oldPlaneX * sin(-rotSpeed) + img->planeY * cos(-rotSpeed);
	}
	if (mlx_is_key_down(param, MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(rotSpeed) - img->dirY * sin(rotSpeed);
		img->dirY = oldDirX * sin(rotSpeed) + img->dirY * cos(rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(rotSpeed) - img->planeY * sin(rotSpeed);
		img->planeY = oldPlaneX * sin(rotSpeed) + img->planeY * cos(rotSpeed);
	}
}

void	moov_player(mlx_key_data_t keydata, void *param)
{
	double	movespeed;
	t_map	*img;
	t_cast	cast;

	img = (t_map *)param;
	movespeed = 0.3;
	moov_up_and_down(keydata, img, movespeed);
	moov_left_and_right(keydata, img, movespeed);
	turn_camera(keydata, img, param);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(img->mlx);
		return ;
	}
	*img = raycasting(img->map, *img, cast);
}

void	moov_camera(mlx_key_data_t keydata, void *param)
{
	t_map	*img;

	img = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(img->mlx);
		return ;
	}
//	*img = raycasting(img->map, *img, *img->cast);
}
