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
	if (img.dirX == 1.0 && img.dirY == 0.0)
		printf("regarde au SUD posX = %f posY = %f\n", img.posX, img.posY);
	if (img.dirX == 0.0 && img.dirY == 1.0)
		printf("regarde au NORD posX = %f posY = %f dirX = %f dirY = %f\n", img.posX, img.posY, img.dirX, img.dirY);
	if (img.dirX == -1.0 && img.dirY == 0.0)
		printf("regarde a l WEST posX = %f posY = %f\n", img.posX, img.posY);
	if (img.dirX == 0.0 && img.dirY == -1.0)
		printf("regarde a l EST posX = %f posY = %f\n", img.posX, img.posY);
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
	img.texture = mlx_load_png("textures/bark.png");
	img.image = mlx_new_image(img.mlx, 1280, 720);
	img = raycasting(map, img, img.cast);
	mlx_loop_hook(img.mlx, moov_player, &img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
