#include "../cub3D.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
    if (x > 0 && y > 0 && x < 1280 && y < 720)
        ((int *)data->addr)[y * 1280 + x] = color;
}

t_map raycasting(t_data map, t_map img)
{
    int color;
    int x;
    int y;
    int w;
    int h;
    int texWidth;
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit; // was there a wall hit?
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double wallX;
    int texX;

    texWidth = 64;
    img.map = map;
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (img.dirX == 1.0 && img.dirY == 0.0)
        color = 0x808000; // SUD
    if (img.dirX == 0.0 && img.dirY == 1.0)
        color = 0xC0C0C0; // NORD
    if (img.dirX == -1.0 && img.dirY == 0.0)
        color = 0xFFFF00; // WEST
    if (img.dirX == 0.0 && img.dirY == -1.0)
        color = 0x00FFFF; // EST
    color = mlx_get_color_value(img.img, color);
    //color = 0x000000; // SUD
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    x = 0;
    y = 0;
   while (x < 1280)
    {
        y = 0;
        while (y < 720)
        {
            ((int *)img.addr)[y * 1280 + x] = color;
            y++;
        }
        x++;
    }
   // mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    w = 1280;
    h = 720;
    y = 0;
    x = 0;
    while (x < w)
    {
        cameraX = 2.0 * (double)x / (double)w - 1.0;
        rayDirX = img.dirX + img.planeX * cameraX;
        rayDirY = img.dirY + img.planeY * cameraX;
        mapX = (int)img.posX;
        mapY = (int)img.posY;

        if (rayDirX == 0.0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1.0 / rayDirX);

        if (rayDirY == 0.0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1.0 / rayDirY);

        if (rayDirX < 0.0)
        {
            stepX = -1;
            sideDistX = (double)(img.posX - (double)mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ((double)mapX + 1.0 - img.posX) * deltaDistX;
        }

        if (rayDirY < 0.0)
        {
            stepY = -1;
            sideDistY = (img.posY - (double)mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ((double)mapY + 1.0 - img.posY) * deltaDistY;
        }

        hit = 0;
        while (hit == 0)
        {
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
            if (img.map.map[mapX][mapY] == '1')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        lineHeight = (int)((double)h / perpWallDist);

        drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h)
            drawEnd = h - 1;

        if (side == 0)
            wallX = img.posY + perpWallDist * rayDirY;
        else
            wallX = img.posX + perpWallDist * rayDirX;
        wallX -= wallX;

        texX = (int)(wallX * (double)texWidth);
        if (side == 0 && rayDirX > 0.0)
            texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0.0)
            texX = texWidth - texX - 1;

        y = drawStart;
        while (y < drawEnd)
        {
			//my_mlx_pixel_put(&img, x, y, color);
            if (img.dirX == 1.0 && img.dirY == 0.0)
                color = 0x05ff00; // SUD
            if (img.dirX == 0.0 && img.dirY == 1.0)
                color = 0x05ff00; // NORD
            if (img.dirX == -1.0 && img.dirY == 0.0)
                color = 0x05ff00; // WEST
            if (img.dirX == 0.0 && img.dirY == -1.0)
                color = 0x00FFFF; // EST
			//color = mlx_get_color_value(img.img, color);
            my_mlx_pixel_put(&img, x, y, color);
            y++;
        }
        x++;
    }
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    return (img);
}

// include all
