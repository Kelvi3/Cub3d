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
	if (keycode == 119)
	{
		if (!img->map.map[(int)img->posX + (int)img->dirX * 1][(int)img->posY])
			img->posX += img->dirX * 1.0;
		// look_nord
	}
	if (keycode == 97)
	{
		return (1);
	}	//look_ouest
	if (keycode == 115)
	{
		return (1);
		//look_sud
	}
	if (keycode == 100)
	{
		return (1);
		//look_est
	}
	if (keycode == 65307)
	{
		return (1);
	}
	return (0);
}

void	moov_camera(t_map img)
{
	mlx_key_hook(img.mlx_win, &change_map, &img);
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
	img.mlx_win = mlx_new_window(img.mlx, 1280, 720, "CUB3D");
	img.floor = mlx_new_image(img.mlx, 1280, 720);
	img.img = mlx_new_image(img.mlx, 1280, 720);
	img = raycasting(map, img);
	img = floorcasting(map, img);
	moov_camera(img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
