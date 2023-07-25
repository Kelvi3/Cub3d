/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:07:27 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 16:25:03 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	dda(t_cast *cast, t_map img)
{
	cast->hit = 0;
	while (cast->hit == 0)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (img.map.map[cast->map_x][cast->map_y] == '1')
			cast->hit = 1;
	}
}

t_map	dir_texture(t_map img, t_cast *cast)
{
	if (cast->side == 0 && cast->ray_dir_x > 0.0)
		img.texture = img.texture_s;
	if (cast->side == 0 && cast->ray_dir_x < 0.0)
		img.texture = img.texture_n;
	if (cast->side == 1 && cast->ray_dir_y < 0.0)
		img.texture = img.texture_w;
	if (cast->side == 1 && cast->ray_dir_y > 0.0)
		img.texture = img.texture_e;
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
		cast->line_height = (int)((double)HEIGHT / cast->perp_wall_dist);
		calculate_lowest_and_highest_pixel(cast);
		if (cast->side == 0)
			cast->wall_x = img.pos_y + cast->perp_wall_dist * cast->ray_dir_y;
		else
			cast->wall_x = img.pos_x + cast->perp_wall_dist * cast->ray_dir_x;
		cast->wall_x -= floor(cast->wall_x);
		img = dir_texture(img, cast);
		cast->tex_x = (int)(cast->wall_x * img.texture->width);
		if (cast->side == 0 && cast->ray_dir_x > 0.0)
			cast->tex_x = img.texture->width - cast->tex_x - 1;
		if (cast->side == 1 && cast->ray_dir_y < 0.0)
			cast->tex_x = img.texture->width - cast->tex_x - 1;
		floor_wall_ceiling(img, cast, map);
		cast->x++;
	}
}

t_map	raycasting(t_data map, t_map img, t_cast cast)
{
	cast.tex_width = 64;
	cast.tex_height = 64;
	cast.y = 0;
	cast.x = 0;
	img.map = map;
	raycasting_loop(img, &cast, map);
	mlx_image_to_window(img.mlx, img.image, 0, 0);
	return (img);
}
