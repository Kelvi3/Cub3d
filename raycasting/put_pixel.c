/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:56:07 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 14:32:26 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	set_rgb(t_rgb *color, t_map img, t_cast *cast)
{
	int	pixel;

	pixel = (img.texture->width * cast->tex_y + cast->tex_x) * img.texture->bytes_per_pixel;
	color->r = img.texture->pixels[pixel];
	color->g = img.texture->pixels[pixel + 1];
	color->b = img.texture->pixels[pixel + 2];
}

static void	pixel_ceiling(t_cast *cast, t_map img, int ceiling)
{
	while (cast->y < cast->draw_start)
	{
		mlx_put_pixel(img.image, cast->x, cast->y, ceiling);
		cast->y++;
	}
}

static void	pixel_floor(t_cast *cast, t_map img, int floor)
{
	while (cast->y < HEIGHT)
	{
		mlx_put_pixel(img.image, cast->x, cast->y, floor);
		cast->y++;
	}
}

void	floor_wall_ceiling(t_map img, t_cast *cast, t_data map)
{
	int		ceiling;
	int		floor;
	t_rgb	color;

	(void)map;
	cast->y = 0;
	ceiling = get_rgba(map.colorf[0], map.colorf[1], map.colorf[2], 255);
	floor = get_rgba(map.colorc[0], map.colorc[1], map.colorc[2], 255);
	pixel_ceiling(cast, img, ceiling);
	cast->step = 1.0 * (double)cast->tex_height / (double)cast->line_height;
	cast->tex_pos = ((double)cast->draw_start - (double)HEIGHT \
			/ 2.0 + (double)cast->line_height / 2.0) * cast->step;
	while (cast->y < cast->draw_end)
	{
		cast->tex_y = (int)cast->tex_pos & (cast->tex_height - 1);
		cast->tex_pos += cast->step;
		set_rgb(&color, img, cast);
		cast->color = get_rgba(color.r, color.g, color.b, 255);
		mlx_put_pixel(img.image, cast->x, cast->y, cast->color);
		cast->y++;
	}
	pixel_floor(cast, img, floor);
}
