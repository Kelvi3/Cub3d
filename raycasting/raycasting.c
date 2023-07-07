#include "../cub3D.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	floor_wall_ceiling(t_map img, t_cast *cast, t_data map)
{
	int	ceiling;
	int	floor;
	int	r;
	int	g;
	int	b;

	(void)map;
	cast->y = 0;
	while (cast->y < cast->drawStart)
	{
		ceiling = get_rgba(map.colorf[0], map.colorf[1], map.colorf[2], 255);
		mlx_put_pixel(img.image, cast->x, cast->y, ceiling);
		cast->y++;
	}
	cast->step = 1.0 * (double)cast->texHeight / (double)cast->lineHeight;
	cast->texPos = ((double)cast->drawStart - (double)HEIGHT / 2.0 + (double)cast->lineHeight / 2.0) * cast->step;
	while (cast->y < cast->drawEnd)
	{
		cast->texY = (int)cast->texPos & (cast->texHeight - 1);
		cast->texPos += cast->step;
		r = img.texture->pixels[(img.texture->width * cast->texY + cast->texX) * img.texture->bytes_per_pixel];
		g = img.texture->pixels[(img.texture->width * cast->texY + cast->texX) * img.texture->bytes_per_pixel + 1];
		b = img.texture->pixels[(img.texture->width * cast->texY + cast->texX) * img.texture->bytes_per_pixel + 2];
		cast->color = get_rgba(r, g, b, 255);
		mlx_put_pixel(img.image, cast->x, cast->y, cast->color);
		cast->y++;
	}
	while (cast->y < HEIGHT)
	{
		floor = get_rgba(map.colorc[0], map.colorc[1], map.colorc[2], 255);
		mlx_put_pixel(img.image, cast->x, cast->y, floor);
		cast->y++;
	}
}

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

void	raycasting_loop(t_map img, t_cast *cast, t_data map)
{
	while (cast->x < WIDTH)
	{
		calculate_pos_and_dir(cast, img);
		calculate_step_and_initial_sidedist(cast, img);
		dda(cast, img);
		if (cast->side == 0)
			cast->perpWallDist = (cast->sideDistX - cast->deltaDistX);
		else
			cast->perpWallDist = (cast->sideDistY - cast->deltaDistY);
		cast->lineHeight = (int)((double)HEIGHT / cast->perpWallDist);
		calculate_lowest_and_highest_pixel(cast);
		cast->texNum = img.map.map[cast->mapX][cast->mapY];
		if (cast->side == 0)
			cast->wallX = img.posY + cast->perpWallDist * cast->rayDirY;
		else
			cast->wallX = img.posX + cast->perpWallDist * cast->rayDirX;
		cast->wallX -= floor(cast->wallX);
		if (cast->side == 0 && cast->rayDirX > 0.0)
			img.texture = img.texture_n;
		if (cast->side == 0 && cast->rayDirX <= 0.0)
			img.texture = img.texture_s;
		if (cast->side == 1 && cast->rayDirX >= 0.0)
			img.texture = img.texture_e;
		if (cast->side == 1 && cast->rayDirX < 0.0)
			img.texture = img.texture_w;
		cast->texX = (int)(cast->wallX * (double)cast->texWidth);
		if (cast->side == 0 && cast->rayDirX > 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		if (cast->side == 1 && cast->rayDirY < 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		floor_wall_ceiling(img, cast, map);
		cast->x++;
	}
}

t_map raycasting(t_data map, t_map img, t_cast cast)
{
	cast.texWidth = 64;
	cast.texHeight = 64;
	cast.x = 0;
	cast.y = 0;
	img.map = map;
	cast.y = 0;
	cast.x = 0;
	raycasting_loop(img, &cast, map);
	mlx_image_to_window(img.mlx, img.image, 0, 0);
	return (img);
}

// include all
