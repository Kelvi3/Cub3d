/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:07:27 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 14:08:16 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	dda(t_cast *cast, t_map img)
{
	cast->hit = 0;
	while (cast->hit == 0)
	{
		if (cast->sideDistX < cast->sideDistY)
		{
			cast->sideDistX += cast->deltaDistX;
			cast->mapX += cast->stepX;
			cast->side = 0;
		}
		else
		{
			cast->sideDistY += cast->deltaDistY;
			cast->mapY += cast->stepY;
			cast->side = 1;
		}
		if (img.map.map[cast->mapX][cast->mapY] == '1')
			cast->hit = 1;
	}
}

t_map	dir_texture(t_map img, t_cast *cast)
{
	if (cast->side == 0 && cast->rayDirX > 0.0)
		img.texture = img.texture_s;
	if (cast->side == 0 && cast->rayDirX < 0.0)
		img.texture = img.texture_n;
	if (cast->side == 1 && cast->rayDirY < 0.0)
		img.texture = img.texture_e;
	if (cast->side == 1 && cast->rayDirY > 0.0)
		img.texture = img.texture_w;
	return (img);
}

void	raycasting_loop(t_map img, t_cast *cast, t_data map)
{
	while (cast->x < WIDTH)
	{
		calculate_pos_and_dir(cast, img);
		calculate_step_and_initial_sidedist(cast, img);
		dda(cast, img);
		calculate_distance_perpendicular_ray(cast);
		cast->lineHeight = (int)((double)HEIGHT / cast->perpWallDist);
		calculate_lowest_and_highest_pixel(cast);
		cast->texNum = img.map.map[cast->mapX][cast->mapY];
		if (cast->side == 0)
			cast->wallX = img.posY + cast->perpWallDist * cast->rayDirY;
		else
			cast->wallX = img.posX + cast->perpWallDist * cast->rayDirX;
		cast->wallX -= floor(cast->wallX);
		img = dir_texture(img, cast);
		cast->texX = (int)(cast->wallX * (double)cast->texWidth);
		if (cast->side == 0 && cast->rayDirX > 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		if (cast->side == 1 && cast->rayDirY < 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		floor_wall_ceiling(img, cast, map);
		cast->x++;
	}
}

t_map	raycasting(t_data map, t_map img, t_cast cast)
{
	cast.texWidth = 64;
	cast.texHeight = 64;
	cast.y = 0;
	cast.x = 0;
	img.map = map;
	raycasting_loop(img, &cast, map);
	mlx_image_to_window(img.mlx, img.image, 0, 0);
	return (img);
}
