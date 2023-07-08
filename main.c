#include "MLX42/include/MLX42/MLX42.h"
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

t_map get_pos_player(t_data map, t_map img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img.dirX = 0.0;
	img.dirY = 0.0;
	img.planeX = 0.0;
	img.planeY = 0.0;
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
					img.planeY = 0.66;
				}
				if (map.map[i][j] == 'N')
				{
					img.dirX = -1.0;
					img.planeY = -0.66;
				}
				if (map.map[i][j] == 'W')
				{
					img.dirY = 1.0;
					img.planeX = -0.66;
				}
				if (map.map[i][j] == 'E')
				{
					img.dirY = -1.0;
					img.planeX = 0.66;
				}
			}
			j++;
		}
		i++;
	}
	return (img);
}

int main(int argc, char **argv)
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
	img.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!img.mlx)
		return (2);
	// TODO : create function vecteur for get dirX dirY
	img.map = map;
	img = get_pos_player(map, img);
	img.texture_n = mlx_load_png("textures/psg.png");
	img.texture_s = mlx_load_png("textures/marseille.png");
	img.texture_e = mlx_load_png("textures/lyon.png");
	img.texture_w = mlx_load_png("textures/bordeaux.png");
	/*
	img.texture_n = mlx_load_png(map.no);
	img.texture_s = mlx_load_png(map.so);
	img.texture_e = mlx_load_png(map.ea);
	img.texture_w = mlx_load_png(map.we);
	*/
	img.image = mlx_new_image(img.mlx, 1280, 720);
	img = raycasting(map, img, img.cast);
	mlx_loop_hook(img.mlx, moov_player, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.image);
	free_all(&map);
	return (0);
}
