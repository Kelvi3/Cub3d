#include "../cub3D.h"

void	my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	if (x > 0 && y > 0 && x < 1280 && y < 720)
		((int *)data->addr)[y * 1280 + x] = color;
}

void	img_pix_put(t_map img, t_cast cast, int color)
{
	char    *pixel;

	pixel = img.addr + (cast.y * 1280 + cast.x * (img.bits_per_pixel / 8));
	*(int *)pixel = color;
}
void	floor_wall_ceiling(t_map img, t_cast cast)
{
	int	x = 0;
	int y = 0;
	cast.y = 0;
   while (x < 1280)
    {
        y = 0;
        while (y < 720)
        {
			img_pix_put(img, cast, cast.color);
          //  ((int *)img.addr)[y * 1280 + x] = color;
            y++;
        }
        x++;
    }
	while (cast.y < cast.drawStart)
	{
		int	color2 = 0xFF000;
		my_mlx_pixel_put(&img, cast.x, cast.y, color2);
		//img_pix_put(img, cast, color2);
		cast.y++;
	}
	while (cast.y < cast.drawEnd)
	{
		//my_mlx_pixel_put(&img, x, y, color);
		if (img.dirX == 1.0 && img.dirY == 0.0)
			cast.color = 0x05ff00; // SUD
		if (img.dirX == 0.0 && img.dirY == 1.0)
			cast.color = 0x05ff00; // NORD
		if (img.dirX == -1.0 && img.dirY == 0.0)
			cast.color = 0x05ff00; // WEST
		if (img.dirX == 0.0 && img.dirY == -1.0)
			cast.color = 0x00FFFF; // EST
		//cast.color = (cast.y * 1280 + cast.x * (img.bits_per_pixel / 8));
		//*(int *)img.addr = cast.color;
		//color = 0x00FFFF;
		//img_pix_put(img, cast, cast.color);
		my_mlx_pixel_put(&img, cast.x, cast.y, cast.color);
		cast.y++;
	}
	while (cast.y < 720)
	{
		int color1 = 0x000FF;
		my_mlx_pixel_put(&img, cast.x, cast.y, color1);
		cast.y++;
	}
}

t_cast	dda(t_cast cast, t_map img)
{
	cast.hit = 0;
	while (cast.hit == 0)
	{
		if (cast.sideDistX < cast.sideDistY)
		{
			cast.sideDistX += cast.deltaDistX;
			cast.mapX += cast.stepX;
			cast.side = 0;
		}
		else
		{
			cast.sideDistY += cast.deltaDistY;
			cast.mapY += cast.stepY;
			cast.side = 1;
		}
		if (img.map.map[cast.mapX][cast.mapY] == '1')
			cast.hit = 1;
	}
	return (cast);
}

t_map raycasting(t_data map, t_map img, t_cast cast)
{
	cast.texWidth = 64;
	cast.x = 0;
	cast.y = 0;
	cast.w = 1280;
	cast.h = 720;
	img.map = map;
//	int	we = 64;
//	int	he = 64;
	img.img = mlx_new_image(img.mlx, 1280, 720);
//	img.img = mlx_xpm_file_to_image(img.mlx, "textures/wall.xpm", &he, &we);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("bpp = %d\n", img.bits_per_pixel);
	if (img.dirX == 1.0 && img.dirY == 0.0)
		cast.color = 0x808000; // SUD
	if (img.dirX == 0.0 && img.dirY == 1.0)
		cast.color = 0xC0C0C0; // NORD
	if (img.dirX == -1.0 && img.dirY == 0.0)
		cast.color = 0xFFFF00; // WEST
	if (img.dirX == 0.0 && img.dirY == -1.0)
		cast.color = 0x00FFFF; // EST
	cast.color = 0x000000; // SUD
   /*while (x < 1280)
    {
        y = 0;
        while (y < 720)
        {
            ((int *)img.addr)[y * 1280 + x] = color;
            y++;
        }
        x++;
    }*/
	while (cast.x < cast.w)
	{
		calculate_pos_and_dir(&cast, img);
		calculate_step_and_initial_sidedist(&cast, img);
		cast = dda(cast, img);
		if (cast.side == 0)
			cast.perpWallDist = (cast.sideDistX - cast.deltaDistX);
		else
			cast.perpWallDist = (cast.sideDistY - cast.deltaDistY);
		cast.lineHeight = (int)((double)cast.h / cast.perpWallDist);
		calculate_lowest_and_highest_pixel(&cast);
		if (cast.side == 0)
			cast.wallX = img.posY + cast.perpWallDist * cast.rayDirY;
		else
			cast.wallX = img.posX + cast.perpWallDist * cast.rayDirX;
		cast.wallX -= cast.wallX;
		cast.texX = (int)(cast.wallX * (double)cast.texWidth);
		if (cast.side == 0 && cast.rayDirX > 0.0)
			cast.texX = cast.texWidth - cast.texX - 1;
		if (cast.side == 1 && cast.rayDirY < 0.0)
			cast.texX = cast.texWidth - cast.texX - 1;
		floor_wall_ceiling(img, cast);
		cast.x++;
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	return (img);
}

// include all
