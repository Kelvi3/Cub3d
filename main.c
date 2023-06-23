#include "cub3D.h"
#include "minilibx-linux/mlx.h"

void	print_all(t_data map)
{
	printf("NO = %s\n", map.no);
	printf("SO = %s\n", map.so);
	printf("WE = %s\n", map.we);
	printf("EA = %s\n", map.ea);

	printf("F = %s\n", map.color_f);
	printf("C = %s\n", map.color_c);
	int	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

/*	./cub3D ./map	= error */

int	change_map(int keycode, t_map *img)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rotSpeed;

	rotSpeed = 0.2;
	if (keycode == 119)
	{
		printf("NORD\n");
		if (img->map.map[(int)img->posX + (int)img->dirX * 1][(int)img->posY] != '1')
			img->posX += img->dirX * 0.1;
		if (img->map.map[(int)img->posX][(int)img->posY + (int)img->dirY * 1] != '1')
			img->posY += img->dirY * 0.1;
	}
	if (keycode == 97)
	{
		printf("OUEST\n");
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(rotSpeed) - img->dirY * sin(rotSpeed);
		img->dirY = oldDirX * sin(rotSpeed) + img->dirY * cos(rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(rotSpeed) - img->planeY * sin(rotSpeed);
		img->planeY = oldPlaneX * sin(rotSpeed) + img->planeY * cos(rotSpeed);
	} // look_ouest
	if (keycode == 115)
	{
		printf("SUD\n");
		if (img->map.map[(int)img->posX + (int)img->dirX * 1][(int)img->posY] != '1')
			img->posX -= img->dirX * 0.1;
		if (img->map.map[(int)img->posX][(int)img->posY + (int)img->dirY * 1] != '1')
			img->posY -= img->dirY * 0.1;
		//look_sud
	}
	if (keycode == 100)
	{
		printf("EST\n");
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(-rotSpeed) - img->dirY * sin(-rotSpeed);
		img->dirY = oldDirX * sin(-rotSpeed) + img->dirY * cos(-rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(-rotSpeed) - img->planeY * sin(-rotSpeed);
		img->planeY = oldPlaneX * sin(-rotSpeed) + img->planeY * cos(-rotSpeed);
		//look_est
	}
	if (keycode == 65307)
	{
		mlx_loop_end(img->mlx);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		return (0);
	}
	printf("dirx = %f\n", img->dirX);
	printf("dirY = %f\n", img->dirY);
	printf("planeX = %f\n", img->planeX);
	printf("PLaneY = %f\n", img->planeY);
	printf("posy = %f\n", img->posX);
	printf("posx = %f\n--------------\n", img->posY);
	*img = raycasting(img->map, *img);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	map;
	t_map	img;

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
	img.posX = 3.5;
	img.posY = 3.5;
	img.dirX = 0.0;
	img.dirY = 1.0;
	// TODO : create function vecteur for get dirX dirY
	img.map = map;
	img.planeX = 0.0;
	img.planeY = 0.66;
	img.mlx_win = mlx_new_window(img.mlx, 1280, 720, "CUB3D");
	img.floor = mlx_new_image(img.mlx, 1280, 720);
	int h = 64;
	int	w = 64;
	img.img = mlx_xpm_file_to_image(img.mlx, "./textures/wall.xpm", &w, &h);
	img.img = mlx_new_image(img.mlx, 1280, 720);
	img.floor = mlx_new_image(img.mlx, 1280, 720);
	img = floorcasting(map, img);
	img = raycasting(map, img);
	//moov_camera(img);
	mlx_key_hook(img.mlx_win, &change_map, &img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
