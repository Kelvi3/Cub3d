#include "../cub3D.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
    if (x > 0 && y > 0 && x < 1280 && y < 720)
        ((int *)data->addr)[y * 1280 + x] = color;
}

t_map   raycasting(t_data map, t_map img)
{
    int     color;
    int x;
    int y;
    int w;
    int h;
    int texWidth;
    int texHeight;
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
    double step;
    double texPos;

	img.posX = 4.0;
    img.posY = 3.0;
    img.dirX = 1.0;
    img.dirY = 0.0;
    // TODO : create function vecteur for get dirX dirY
    img.planeX = 0.0;
    img.planeY = 0.66;
    texWidth = 64;
    texHeight = 64;
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
    w = 1280;
    h = 720;
    y = 0;
    x = 0;
    while (x < w)
    {
        cameraX = 2 * (double)x / (double)w - 1;
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

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = ((double)img.posX - (double)mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ((double)mapX + 1.0 - (double)img.posX) * deltaDistX;
        }

        if (rayDirY < 0.0)
        {
            stepY = -1;
            sideDistY = ((double)img.posY - (double)mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ((double)mapY + 1.0 - (double)img.posY) * deltaDistY;
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
            if (img.map.map[mapX][mapY] > '0')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        if (perpWallDist == 0.0)
            perpWallDist = 1.0;

        lineHeight = h / (int)perpWallDist;

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

        texX = (int)wallX * texWidth;
        if (side == 0 && rayDirX > 0.0)
            texX = texWidth - texX - 1;
        if (side == 1 && rayDirY < 0.0)
            texX = texWidth - texX - 1;

        step = 1.0 * (double)texHeight / (double)lineHeight;
        texPos = ((double)drawStart - (double)h / 2 + (double)lineHeight / 2) * step;

        y = drawStart;
        while (y < drawEnd)
        {
            texPos += step;
            my_mlx_pixel_put(&img, x, y, color);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    return (img);
}

// include all
