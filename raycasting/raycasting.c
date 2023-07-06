#include "../cub3D.h"

#define BPP sizeof(int32_t)
void	floor_wall_ceiling(t_map img, t_cast cast, t_data map)
{
	//int	ceiling;
	//int	floor;
	(void)map;
	cast.y = 0;
	/*while (cast.y < cast.drawStart)
	{
		ceiling = (map.colorc[0] << 16) | (map.colorc[1] << 8) | map.colorc[2];
		mlx_put_pixel(img.image, cast.x, cast.y, ceiling);
		cast.y++;
	}*/
	
	while (cast.y < cast.drawEnd)
	{
		if (img.dirX == 1.0 && img.dirY == 0.0)
			cast.color = 0x3272A3; // SUD
		if (img.dirX == 0.0 && img.dirY == 1.0)
			cast.color = 0x3200A3; // NORD
		if (img.dirX == -1.0 && img.dirY == 0.0)
			cast.color = 0xFF323A; // WEST
		if (img.dirX == 0.0 && img.dirY == -1.0)
			cast.color = 0xFF0004; // EST
			
		cast.color = 0xFF0004; // EST
		mlx_put_pixel(img.image, cast.x, cast.y, cast.color);
		cast.y++;
	}
	/*while (cast.y < HEIGHT)
	{
		floor = (map.colorf[0] << 16) | (map.colorf[1] << 8) | map.colorf[2];
		mlx_put_pixel(img.image, cast.x, cast.y, floor);
		cast.y++;
	}*/
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
		if (cast->side == 0)
			cast->wallX = img.posY + cast->perpWallDist * cast->rayDirY;
		else
			cast->wallX = img.posX + cast->perpWallDist * cast->rayDirX;
		cast->wallX -= cast->wallX;
		cast->texX = (int)(cast->wallX * (double)cast->texWidth);
		if (cast->side == 0 && cast->rayDirX > 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		if (cast->side == 1 && cast->rayDirY < 0.0)
			cast->texX = cast->texWidth - cast->texX - 1;
		floor_wall_ceiling(img, *cast, map);
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
	//img.img = mlx_xpm_file_to_image(img.mlx, "textures/wall.xpm", &he, &we);

	//img.texture = mlx_load_png("textures/bark.png");
	//img.image = mlx_texture_to_image(img.mlx, img.texture);
	img.image = mlx_new_image(img.mlx, 1280, 720);
	//image = mlx_new_image(img.mlx, 1280, 720);
	/*if (img.dirX <= 1.0 && img.dirY >= 0.0)
		cast.color = 0x3272A3; // SUD
	if (img.dirX >= 0.0 && img.dirY <= 1.0)
		cast.color = 0x3200A3; // NORD
	if (img.dirX >= -1.0 && img.dirY <= 0.0)
		cast.color = 0x3200A3; // WEST
	if (img.dirX <= 0.0 && img.dirY >= -1.0)
		cast.color = 0x140004; // EST*/
	/*while (cast.x < 1280)
	{
		cast.y = 0;
		while (cast.y < 720)
		{
			((int *)img.addr)[cast.y * 1280 + cast.x] = cast.color;
			cast.y++;
		}
		cast.x++;
	}*/
	cast.y = 0;
	cast.x = 0;
	raycasting_loop(img, &cast, map);
	mlx_image_to_window(img.mlx, img.image, 0, 0);
	//mlx_put_image_to_window(img.mlx, img.mlx_win, image, 0, 0);
	return (img);
}

// include all
