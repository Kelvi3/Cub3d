#include "./include.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

int	main(int argc, char **argv)
{
	t_data	img;
	int		color;
	int		x;
	int		y;
	int		w;
	int		h;
	double posX;
	double posY; // x and y start position
	double dirX;
	double dirY;	 // initial direction vector
	double planeX;
	double planeY;
	int texWidth;
	int texHeight;
	//int mapWidth  = 24;
	//int	mapHeight = 24;
	long int i;

	posX = 5.0;
	posY = 3.0;
	dirX = -1.0;
	dirY = 0.0;
	planeX = 0.0;
	planeY = 0.66;
	texWidth  = 64;
	texHeight = 64;
	(void)argc;
	(void)argv;
	
	i = 0;
	img.map = malloc(sizeof(char *) * 7);
	while (i < 7)
	{
		img.map[i] = malloc(sizeof(char) * 23);
		i++;
	}
	img.map[0] = "111111111111111111111";
	img.map[1] = "100000000000000000001";
	img.map[2] = "100000000000000000001";
	img.map[3] = "10000P000000000000001";
	img.map[4] = "100000000000000000001";
	img.map[5] = "111111111111111111111";
	img.map[6] = NULL;
	img.mlx = mlx_init();
	if (!img.mlx)
		return (0);
	img.mlx_win = mlx_new_window(img.mlx, 1023, 512, "CUB3D");
	color = 0xFFE6FF;
	w = 1023;
	h = 512;
	int buffer[512][1023];
	x = 0;
	while (x < texWidth)
		x++;
	i = 0;
	long int **texture = (long int **)malloc(8 * sizeof(long int *));
	i = 0;
	while (i < 8)
	{
		texture[i] = (long int *)malloc(texWidth * texHeight * sizeof(long int));
		i++;
	}
	// Redimensionnement de la mémoire
	i = 0;
	while (i < 8)
	{
		texture[i] = (long int *)realloc(texture[i], texWidth * texHeight * sizeof(long int));
		i++;
	}
	x = 0;
	while (x < texWidth)
		x++;
	y = 0;
	while (y < texHeight)
	{
		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		// int xcolor = x * 256 / texWidth;
		int ycolor = y * 256 / texHeight;
		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);	 // flat red texture with black cross
		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	 // sloped greyscale
		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;				 // sloped yellow gradient
		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
		texture[4][texWidth * y + x] = 256 * xorcolor;								 // xor green
		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);			 // red bricks
		texture[6][texWidth * y + x] = 65536 * ycolor;								 // red gradient
		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;				 // flat grey texture
		y++;
	}
	i = 0;
	while (i < 1000)
	{
		x = 0;
		while (x < w)
		{
			// calculate ray position and direction
			double cameraX = 2 * x / (double)w - 1; // x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			// which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			// length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			// length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			double perpWallDist;

			// what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; // was there a wall hit?
			int side;	 // was a NS or a EW wall hit?

			// calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			// perform DDA
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				//printf("x = %i y = %i\n", mapX, mapY);
				if (img.map[mapX][mapY] > 0)
					hit = 1;
			}

			// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);

			// Calculate height of line to draw on screen
			printf("eeeeee = %i\n", h);
			int lineHeight = (int)(h / perpWallDist);
			if (perpWallDist == 0)
			{
				perpWallDist = h;
			}
			// calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			// texturing calculations
			int texNum = img.map[mapX][mapY] - 1; // 1 subtracted from it so that texture 0 can be used!

			// calculate value of wallX
			double wallX; // where exactly the wall was hit
			if (side == 0)
				wallX = posY + perpWallDist * rayDirY;
			else
				wallX = posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			// x coordinate on the texture

			int texX = (int)wallX * (double)texWidth;
			if (side == 0 && rayDirX > 0)
				texX = texWidth - texX - 1;
			if (side == 1 && rayDirY < 0)
				texX = texWidth - texX - 1;

			// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart  - h / 2 + lineHeight / 2) * step;
			int	y;
			y = drawStart;
			printf("y = %i drazend = %i\n", y, drawEnd);
			while (y < drawEnd)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				color = texture[texNum][texHeight * texY + texX];
				// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if (side == 1)
					color = (color >> 1) & 8355711;
				buffer[y][x] = color;
				img.height = 64;
				img.width = 64;
				printf("fniowfeow\n");
				mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				mlx_pixel_put(img.mlx, img.mlx_win, x, y, color);
				//img.wall = mlx_xpm_file_to_image(img.mlx, "./img/grass.xpm",
				//								 &img.width, &img.height);
				//mlx_put_image_to_window(img.mlx, img.mlx_win, img.wall, x, y);
				y++;
			}
			x++;
		}
	}
		//drawBuffer(buffer[0]);
		// mlx_destroy_image(img.mlx, img.wall);
		// display_map(img.map, img);
		mlx_loop(img.mlx);
	}
