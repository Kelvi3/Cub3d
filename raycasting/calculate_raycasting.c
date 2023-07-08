/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:04:58 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 14:06:39 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculate_pos_and_dir(t_cast *cast, t_map img)
{
	cast->cameraX = 2.0 * (double)cast->x / (double)WIDTH - 1.0;
	cast->rayDirX = img.dirX + img.planeX * cast->cameraX;
	cast->rayDirY = img.dirY + img.planeY * cast->cameraX;
	cast->mapX = (int)img.posX;
	cast->mapY = (int)img.posY;
}

void	step_and_init_sidedist(t_cast *cast)
{
	if (cast->rayDirX == 0.0)
		cast->deltaDistX = 1e30;
	else
		cast->deltaDistX = fabs(1.0 / cast->rayDirX);
	if (cast->rayDirY == 0.0)
		cast->deltaDistY = 1e30;
	else
		cast->deltaDistY = fabs(1.0 / cast->rayDirY);
}

void	calculate_step_and_initial_sidedist(t_cast *cast, t_map img)
{
	step_and_init_sidedist(cast);
	if (cast->rayDirX < 0.0)
	{
		cast->stepX = -1;
		cast->sideDistX = ((double)(img.posX - (double)cast->mapX)) \
					* cast->deltaDistX;
	}
	else
	{
		cast->stepX = 1;
		cast->sideDistX = ((double)cast->mapX + 1.0 - img.posX) \
						* cast->deltaDistX;
	}
	if (cast->rayDirY < 0.0)
	{
		cast->stepY = -1;
		cast->sideDistY = (img.posY - (double)cast->mapY) \
						* cast->deltaDistY;
	}
	else
	{
		cast->stepY = 1;
		cast->sideDistY = ((double)cast->mapY + 1.0 - img.posY) \
						* cast->deltaDistY;
	}
}

void	calculate_lowest_and_highest_pixel(t_cast *cast)
{
	cast->drawStart = -cast->lineHeight / 2 + HEIGHT / 2;
	if (cast->drawStart < 0)
		cast->drawStart = 0;
	cast->drawEnd = cast->lineHeight / 2 + HEIGHT / 2;
	if (cast->drawEnd >= HEIGHT)
		cast->drawEnd = HEIGHT - 1;
}

void	calculate_distance_perpendicular_ray(t_cast *cast)
{
	if (cast->side == 0)
		cast->perpWallDist = (cast->sideDistX - cast->deltaDistX);
	else
		cast->perpWallDist = (cast->sideDistY - cast->deltaDistY);
}
