#include	"cub3D.h"
/*
static void	moov_up_and_down(int keycode, t_map *img, double movespeed)
{
	if (keycode == 119)
	{
		if (img->map.map[(int)(img->posX + img->dirX)][(int)img->posY] != '1')
			img->posX += img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirY)] != '1')
			img->posY += img->dirY * movespeed;
	}
	if (keycode == 115)
	{
		if (img->map.map[(int)(img->posX - img->dirX)][(int)img->posY] != '1')
			img->posX -= img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY - img->dirY)] != '1')
			img->posY -= img->dirY * movespeed;
	}
}

static void	moov_left_and_right(int keycode, t_map *img, double movespeed)
{
	if (keycode == 97)
	{
		if (img->map.map[(int)(img->posX + img->dirY)][(int)(img->posY)] != '1')
			img->posX += img->dirY * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + (-img->dirX))] != '1')
			img->posY += (-img->dirX) * movespeed;
	}
	if (keycode == 100)
	{
		if (img->map.map[(int)(img->posX + (-img->dirY))][(int)img->posY] != '1')
			img->posX += (-img->dirY) * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirX)] != '1')
			img->posY += img->dirX * movespeed;
	}
}

static void	turn_camera(int keycode, t_map *img)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = 0.2;
	if (keycode == 65361)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(-rotSpeed) - img->dirY * sin(-rotSpeed);
		img->dirY = oldDirX * sin(-rotSpeed) + img->dirY * cos(-rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(-rotSpeed) - img->planeY * sin(-rotSpeed);
		img->planeY = oldPlaneX * sin(-rotSpeed) + img->planeY * cos(-rotSpeed);
	}
	if (keycode == 65363)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(rotSpeed) - img->dirY * sin(rotSpeed);
		img->dirY = oldDirX * sin(rotSpeed) + img->dirY * cos(rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(rotSpeed) - img->planeY * sin(rotSpeed);
		img->planeY = oldPlaneX * sin(rotSpeed) + img->planeY * cos(rotSpeed);
	}
}

int	moov_player(int keycode, t_map *img, t_cast cast)
{
	double	movespeed;

	movespeed = 0.3;
	moov_up_and_down(keycode, img, movespeed);
	moov_left_and_right(keycode, img, movespeed);
	turn_camera(keycode, img);
	if (keycode == 65307)
	{
		mlx_loop_end(img->mlx);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		return (0);
	}
	*img = raycasting(img->map, *img, cast);
	return (0);
}*/
