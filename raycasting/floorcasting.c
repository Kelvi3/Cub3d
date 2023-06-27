#include "../cub3D.h"

t_map	floorcasting(t_data map, t_map img)
{
	double	rayDirX0;
	double	rayDirY0;
	double	rayDirX1;
	double	rayDirY1;
	double	posZ;	
	double	rowDistance;
	double	floorStepX;
	double	floorStepY;
	double	floorX;
	double	floorY;
	int		p;
	int		w;
	int		h;
	int		y;
	int		x;
	int		color;

	(void)map;
	y = 0;
	x = 0;
	p = 0;
	h = 720;
	w = 1280;
	posZ = 0;
	rowDistance = 0;
	img.img = mlx_new_image(img.mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (y < h)
	{
		rayDirX0 = img.dirX - img.planeX;
		rayDirY0 = img.dirY - img.planeY;
		rayDirX1 = img.dirX - img.planeX;
		rayDirY1 = img.dirY - img.planeY;
		posZ = 0.5 * (double)h;
		
		p = y - h / 2;
		
		rowDistance = posZ / (double)p;

		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / (double)w;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / (double)w;

		floorX = img.posX + rowDistance * rayDirX0;
		floorY = img.posY + rowDistance * rayDirY0;
		x = 0;	
		while (++x < w)
		{
			/*int		texWidth = 64;
			int		texHeight = 64;
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
			int tx = (texWidth * (int)(floorX - cellX)) & (texWidth - 1);
			int ty = (texHeight * (int)(floorY - cellY)) & (texHeight - 1);
			*/floorX += floorStepX;
			floorY += floorStepY;
		
			color = 0x000FF;
			int color2 = 0xFF0000;
			my_mlx_pixel_put(&img, x, y, color);
			my_mlx_pixel_put(&img, x, h - y - 1, color2);
		}
		y++;
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.floor, x, y);
	return (img);
}
