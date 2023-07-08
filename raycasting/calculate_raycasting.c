/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_raycasting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:04:58 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 14:37:08 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	calculate_pos_and_dir(t_cast *cast, t_map img)
{
	cast->camera_x = 2.0 * (double)cast->x / (double)WIDTH - 1.0;
	cast->ray_dir_x = img.dir_x + img.plane_x * cast->camera_x;
	cast->ray_dir_y = img.dir_y + img.plane_y * cast->camera_x;
	cast->map_x = (int)img.pos_x;
	cast->map_y = (int)img.pos_y;
}

void	step_and_init_sidedist(t_cast *cast)
{
	if (cast->ray_dir_x == 0.0)
		cast->delta_dist_x = 1e30;
	else
		cast->delta_dist_x = fabs(1.0 / cast->ray_dir_x);
	if (cast->ray_dir_y == 0.0)
		cast->delta_dist_y = 1e30;
	else
		cast->delta_dist_y = fabs(1.0 / cast->ray_dir_y);
}

void	calculate_step_and_initial_sidedist(t_cast *cast, t_map img)
{
	step_and_init_sidedist(cast);
	if (cast->ray_dir_x < 0.0)
	{
		cast->step_x = -1;
		cast->side_dist_x = ((double)(img.pos_x - (double)cast->map_x)) \
					* cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist_x = ((double)cast->map_x + 1.0 - img.pos_x) \
						* cast->delta_dist_x;
	}
	if (cast->ray_dir_y < 0.0)
	{
		cast->step_y = -1;
		cast->side_dist_y = (img.pos_y - (double)cast->map_y) \
						* cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist_y = ((double)cast->map_y + 1.0 - img.pos_y) \
						* cast->delta_dist_y;
	}
}

void	calculate_lowest_and_highest_pixel(t_cast *cast)
{
	cast->draw_start = -cast->line_height / 2 + HEIGHT / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	cast->draw_end = cast->line_height / 2 + HEIGHT / 2;
	if (cast->draw_end >= HEIGHT)
		cast->draw_end = HEIGHT - 1;
}

void	calculate_distance_perpendicular_ray(t_cast *cast)
{
	if (cast->side == 0)
		cast->perp_wall_dist = (cast->side_dist_x - cast->delta_dist_x);
	else
		cast->perp_wall_dist = (cast->side_dist_y - cast->delta_dist_y);
}
