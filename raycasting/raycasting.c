#include "../cub3D.h"

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	if (x > 0 && y > 0 && x < 1280 && y < 720)
		((int *)data->addr)[y * 1280 + x] = color;
}

void	my_mlx_pixel_put2(char	*addr, int x, int y, int color)
{
	if (x > 0 && y > 0 && x < 1280 && y < 720)
		((int *)addr)[y * 1280 + x] = color;
}

void	img_pix_put(t_map img, int x, int y, int color)
{
	char    *pixel;

	pixel = NULL;
	color = (y * 1280 + x * (img.bits_per_pixel / 8));
	*(int *)pixel = color;
}

void	floor_wall_ceiling(t_map img, t_cast cast, t_data map, char *addr, int bpp)
{
	int	ceiling;
	int	floor;

	cast.y = 0;
	printf("drawstart = %d\n", cast.drawStart);
	while (cast.y < cast.drawStart)
	{
		ceiling = (map.colorc[0] << 16) | (map.colorc[1] << 8) | map.colorc[2];
		my_mlx_pixel_put(&img, cast.x, cast.y, ceiling);
		cast.y++;
	}
	
	while (cast.y < 64)//cast.drawEnd)
	{
		if (img.dirX == 1.0 && img.dirY == 0.0)
			cast.color = 0x3272A3; // SUD
		if (img.dirX == 0.0 && img.dirY == 1.0)
			cast.color = 0x3200A3; // NORD
		if (img.dirX == -1.0 && img.dirY == 0.0)
			cast.color = 0x32323A; // WEST
		if (img.dirX == 0.0 && img.dirY == -1.0)
			cast.color = 0x140004; // EST
		//cast.color = (cast.y * 1280 + cast.x * (img.bits_per_pixel / 8));
		//*(int *)img.addr = cast.color;
	//	img_pix_put(img, cast.x, cast.y, cast.color);
		cast.color = (cast.y * 1280 + cast.x * (bpp / 8));
		my_mlx_pixel_put2(addr, cast.x, cast.y, cast.color);
			//my_mlx_pixel_put(&img, cast.x, cast.y, cast.color);
		cast.y++;
	}
	while (cast.y < HEIGHT)
	{
		floor = (map.colorf[0] << 16) | (map.colorf[1] << 8) | map.colorf[2];
		my_mlx_pixel_put(&img, cast.x, cast.y, floor);
		cast.y++;
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

void	raycasting_loop(t_map img, t_cast *cast, t_data map, char *addr, int bpp)
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
		floor_wall_ceiling(img, *cast, map, addr, bpp);
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
	img.img = mlx_new_image(img.mlx, 1280, 720);
	//img.img = mlx_xpm_file_to_image(img.mlx, "textures/wall.xpm", &he, &we);
	char	*addr;
	void	*image;
	int		bpp;
	int		line_length;
	int 	endian;
	image = mlx_xpm_file_to_image(img.mlx, "textures/wall.xpm", &cast.texWidth, &cast.texHeight);
	//image = mlx_new_image(img.mlx, 1280, 720);
	addr = mlx_get_data_addr(image, &bpp, &line_length, &endian);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("endian = %d\n", img.endian);
	printf("bpp = %d\n", img.bits_per_pixel);
	/*if (img.dirX <= 1.0 && img.dirY >= 0.0)
		cast.color = 0x3272A3; // SUD
	if (img.dirX >= 0.0 && img.dirY <= 1.0)
		cast.color = 0x3200A3; // NORD
	if (img.dirX >= -1.0 && img.dirY <= 0.0)
		cast.color = 0x3200A3; // WEST
	if (img.dirX <= 0.0 && img.dirY >= -1.0)
		cast.color = 0x140004; // EST*/
	printf("dirX = %f\n", img.dirX);
	printf("dirY = %f\n", img.dirY);
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
	raycasting_loop(img, &cast, map, addr, bpp);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_put_image_to_window(img.mlx, img.mlx_win, image, 0, 0);
	return (img);
}

// include all
