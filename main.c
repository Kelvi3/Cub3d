#include "cub3D.h"

void print_all(t_data map)
{
	printf("NO = %s\n", map.no);
	printf("SO = %s\n", map.so);
	printf("WE = %s\n", map.we);
	printf("EA = %s\n", map.ea);

	printf("F = %s\n", map.color_f);
	printf("C = %s\n", map.color_c);
	int i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

/*	./cub3D ./map	= error */

int change_map(int keycode, t_map *img)
{
	double oldDirX;
	double oldPlaneX;
	double rotSpeed;
	double	movespeed;

	rotSpeed = 0.2;
	movespeed = 0.5;
	if (keycode == 119)
	{
		if (img->map.map[(int)(img->posX + img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX += img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirY * 1.0)] != '1')
			img->posY += img->dirY * movespeed;
	} // avant
	if (keycode == 115)
	{
		if (img->map.map[(int)(img->posX - img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX -= img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY - img->dirY * 1.0)] != '1')
			img->posY -= img->dirY * movespeed;
	} // recule
	if (keycode == 65363)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(-rotSpeed) - img->dirY * sin(-rotSpeed);
		img->dirY = oldDirX * sin(-rotSpeed) + img->dirY * cos(-rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(-rotSpeed) - img->planeY * sin(-rotSpeed);
		img->planeY = oldPlaneX * sin(-rotSpeed) + img->planeY * cos(-rotSpeed);
	} // tourne_camera droite
	if (keycode == 65361)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(rotSpeed) - img->dirY * sin(rotSpeed);
		img->dirY = oldDirX * sin(rotSpeed) + img->dirY * cos(rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(rotSpeed) - img->planeY * sin(rotSpeed);
		img->planeY = oldPlaneX * sin(rotSpeed) + img->planeY * cos(rotSpeed);
	} // tourne camera gauche
	if (keycode == 65307) // ESC
	{
		mlx_loop_end(img->mlx);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		return (0);
	}
	*img = raycasting(img->map, *img);
	return (0);
}

t_map get_pos_player(t_data map, t_map img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img.dirX = 0.0;
	img.dirY = 0.0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j] != '\0' && map.map[i][j] != '\n')
		{
			if (map.map[i][j] == 'E' || map.map[i][j] == 'W'
				|| map.map[i][j] == 'S' || map.map[i][j] == 'N')
			{
				img.posX = (double)i + 0.5;
				img.posY = (double)j + 0.5;
				if (map.map[i][j] == 'S')
				{
					img.dirX = 1.0;
					img.dirY = 0.0;
				}
				if (map.map[i][j] == 'N')
				{
					img.dirX = 0.5;
					img.dirY = 1.0;
				}
				if (map.map[i][j] == 'W')
				{
					img.dirX = -1.0;
					img.dirY = 0.0;
				}
				if (map.map[i][j] == 'E')
				{
					img.dirX = 0.0;
					img.dirY = -1.0;
				}
			}
			j++;
		}
		i++;
	}
	if (img.dirX == 1.0 && img.dirY == 0.0)
		printf("regarde au SUD posX = %f posY = %f\n", img.posX, img.posY);
	if (img.dirX == 0.0 && img.dirY == 1.0)
		printf("regarde au NORD posX = %f posY = %f\n", img.posX, img.posY);
	if (img.dirX == -1.0 && img.dirY == 0.0)
		printf("regarde a l WEST posX = %f posY = %f\n", img.posX, img.posY);
	if (img.dirX == 0.0 && img.dirY == -1.0)
		printf("regarde a l EST posX = %f posY = %f\n", img.posX, img.posY);
	return (img);
}

int main(int argc, char **argv)
{
	t_data map;
	t_map img;

	if (argc != 2)
	{
		ft_putstr_fd("Error arg\n", 2);
		return (1);
	}
	init_value_data(&map);
	check_extension(argv[1], ".cub");
	add_all_cube(argv, &map);
	if (parse(&map) == 1)
	{
		print_all(map);
		free_all(&map);
		return (1);
	}
	print_all(map);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (2);
	img = get_pos_player(map, img);
	img.planeX = 0.0;
	img.planeY = 0.66;
	img.mlx_win = mlx_new_window(img.mlx, 1280, 720, "CUB3D");
	img.img = mlx_new_image(img.mlx, 1280, 720);
	img = raycasting(map, img);
	mlx_key_hook(img.mlx_win, &change_map, &img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
