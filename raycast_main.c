#include "./include.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

t_data init_map()
{
    int i;
    int j;
    int texWidth;
    int texHeight;
    t_data img;

    texWidth = 64;
    texHeight = 64;
    i = 0;
    j = 0;
    img.map = malloc(sizeof(char *) * 7);
    while (i < 7)
    {
        img.map[i] = malloc(sizeof(char) * 23);
        j = 0;
        while (j < 23)
        {
            img.map[i][j] = 0;
            j++;
        }
        i++;
    }
    j = 0;
    img.height = texHeight;
    img.width = texWidth;
    img.map[0] = "111111111111111111111";
    img.map[1] = "100000000000000000001";
    img.map[2] = "100000000000000000001";
    img.map[3] = "101000000000000000001";
    img.map[4] = "1000N0000000000000001";
    img.map[5] = "111111111111111111111";
    img.map[6] = NULL;
    img.mlx = mlx_init();
    if (!img.mlx)
        return (img);
    i = 0;
    while (img.map[i])
    {
        printf("step = %i %s\n", i, img.map[i]);
        i++;
    }
    return (img);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    if (x > 0 && y > 0 && x < 1280 && y < 720)
        ((int *)data->addr)[y * 1280 + x] = color;
}

int main(int argc, char **argv)
{
    int color;
    t_data img;
    int x;
    int y;
    int w;
    int h;
    double posX;
    double posY; // x and y start position
    double dirX;
    double dirY; // initial direction vector
    double planeX;
    double planeY;
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
    int texNum;
    double wallX;
    int texX;
    double step;
    double texPos;
    int texY;
    int i;
    int j;

    (void)argc;
    (void)argv;
    posX = 4.0;
    posY = 3.0;
    dirX = -1.0;
    dirY = 0.0;
    // TODO : create function vecteur for get dirX dirY
    planeX = 0.0;
    planeY = 0.66;
    texWidth = 64;
    texHeight = 64;
    i = 0;
    img = init_map();
    img.mlx_win = mlx_new_window(img.mlx, 1280, 720, "CUB3D");
    img.img = mlx_new_image(img.mlx, 1280, 720);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    if (dirX == 1.0 && dirY == 0.0)
        color = 0x808000; // SUD
    if (dirX == 0.0 && dirY == 1.0)
        color = 0xC0C0C0; // NORD
    if (dirX == -1.0 && dirY == 0.0)
        color = 0xFFFF00; // WEST
    if (dirX == 0.0 && dirY == -1.0)
        color = 0x00FFFF; // EST
    w = 1280;
    h = 720;
    i = 0;
    j = 0;
    y = 0;
    i = 0;
    x = 0;
    while (x < w)
    {
        cameraX = 2 * (double)x / (double)w - 1;
        rayDirX = dirX + planeX * cameraX;
        rayDirY = dirY + planeY * cameraX;
        mapX = (int)posX;
        mapY = (int)posY;

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
            sideDistX = ((double)posX - (double)mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = ((double)mapX + 1.0 - (double)posX) * deltaDistX;
        }

        if (rayDirY < 0.0)
        {
            stepY = -1;
            sideDistY = ((double)posY - (double)mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = ((double)mapY + 1.0 - (double)posY) * deltaDistY;
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
            if (img.map[mapX][mapY] > '0')
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

        texNum = (int)img.map[mapX][mapY] - 1;
        if (side == 0)
            wallX = posY + perpWallDist * rayDirY;
        else
            wallX = posX + perpWallDist * rayDirX;
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
            texY = (int)texPos & (texHeight - 1);
            texPos += step;
            my_mlx_pixel_put(&img, x, y, color);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    mlx_loop(img.mlx);
}
// y = verticale
// x = horizontale