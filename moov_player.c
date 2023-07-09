/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:00:11 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/09 14:03:46 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3D.h"

static void	moov_up_and_down(t_map *img, double movespeed)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_W))
	{
		if (img->map.map[(int)(img->pos_x + img->dir_x)][(int)img->pos_y] \
				!= '1')
			img->pos_x += img->dir_x * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + img->dir_y)] \
				!= '1')
			img->pos_y += img->dir_y * movespeed;
	}
	if (mlx_is_key_down(img->mlx, MLX_KEY_S))
	{
		if (img->map.map[(int)(img->pos_x - img->dir_x)][(int)img->pos_y] \
				!= '1')
			img->pos_x -= img->dir_x * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y - img->dir_y)] \
				!= '1')
			img->pos_y -= img->dir_y * movespeed;
	}
}

static void	moov_left_and_right(t_map *img, double movespeed)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_D))
	{
		if (img->map.map[(int)(img->pos_x + img->dir_y)][(int)(img->pos_y)] \
				!= '1')
			img->pos_x += img->dir_y * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + (-img->dir_x))]
				!= '1')
			img->pos_y += (-img->dir_x) * movespeed;
	}
	if (mlx_is_key_down(img->mlx, MLX_KEY_A))
	{
		if (img->map.map[(int)(img->pos_x + (-img->dir_y))][(int)img->pos_y] \
				!= '1')
			img->pos_x += (-img->dir_y) * movespeed;
		if (img->map.map[(int)img->pos_x][(int)(img->pos_y + img->dir_x)] \
				!= '1')
			img->pos_y += img->dir_x * movespeed;
	}
}

static void	key_right(t_map *img, double old_dir_x, \
		double old_plane_x, double rot_speed)
{
	if (mlx_is_key_down(img->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = img->dir_x;
		img->dir_x = img->dir_x * cos(-rot_speed) - img->dir_y \
							* sin(-rot_speed);
		img->dir_y = old_dir_x * sin(-rot_speed) + img->dir_y * cos(-rot_speed);
		old_plane_x = img->plane_x;
		img->plane_x = img->plane_x * cos(-rot_speed) - img->plane_y \
							* sin(-rot_speed);
		img->plane_y = old_plane_x * sin(-rot_speed) + img->plane_y \
							* cos(-rot_speed);
	}
}

static void	turn_camera(t_map *img)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.2;
	old_dir_x = 0;
	old_plane_x = 0;
	key_right(img, old_dir_x, old_plane_x, rot_speed);
	if (mlx_is_key_down(img->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = img->dir_x;
		img->dir_x = img->dir_x * cos(rot_speed) - img->dir_y * sin(rot_speed);
		img->dir_y = old_dir_x * sin(rot_speed) + img->dir_y * cos(rot_speed);
		old_plane_x = img->plane_x;
		img->plane_x = img->plane_x * cos(rot_speed) - img->plane_y \
						* sin(rot_speed);
		img->plane_y = old_plane_x * sin(rot_speed) + img->plane_y \
						* cos(rot_speed);
	}
}

void	moov_player(void *param)
{
	double	movespeed;
	t_map	*img;

	img = (t_map *)param;
	movespeed = 0.1;
	moov_up_and_down(img, movespeed);
	moov_left_and_right(img, movespeed);
	turn_camera(img);

	if (mlx_is_key_down(img->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(img->mlx);
		free_all(&img->map);
		exit(0);
	}
	*img = raycasting(img->map, *img, (*img).cast);
}
