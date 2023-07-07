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

/*	./cub3D ./map	= error */

void	change_map(mlx_key_data_t keydata, void *param)
{
	double oldDirX;
	double oldPlaneX;
	double rotSpeed;
	double	movespeed;
	t_map	*img;

	img = (t_map *)param;
	rotSpeed = 0.2;
	movespeed = 0.3;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX + img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX += img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirY * 1.0)] != '1')
			img->posY += img->dirY * movespeed;
	} // avant
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)(img->posX - img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX -= img->dirX * movespeed;
		if (img->map.map[(int)img->posX][(int)(img->posY - img->dirY * 1.0)] != '1')
			img->posY -= img->dirY * movespeed;
	} // recule
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)img->posX][(int)(img->posY + img->dirY * 1.0)] != '1')
			img->posY += img->dirX * movespeed;
		else if (img->map.map[(int)(img->posX + img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX += img->dirX * movespeed;

	} // a droite
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (img->map.map[(int)img->posX][(int)(img->posY - img->dirY * 1.0)] != '1')
			img->posY -= img->dirX * movespeed;
		else if (img->map.map[(int)(img->posX - img->dirX * 1.0)][(int)img->posY] != '1')
			img->posX -= img->dirX * movespeed;
	} // a gauche
	if (mlx_is_key_down(param, MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(-rotSpeed) - img->dirY * sin(-rotSpeed);
		img->dirY = oldDirX * sin(-rotSpeed) + img->dirY * cos(-rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(-rotSpeed) - img->planeY * sin(-rotSpeed);
		img->planeY = oldPlaneX * sin(-rotSpeed) + img->planeY * cos(-rotSpeed);
	} // tourne_camera droite
	if (mlx_is_key_down(param, MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
	{
		oldDirX = img->dirX;
		img->dirX = img->dirX * cos(rotSpeed) - img->dirY * sin(rotSpeed);
		img->dirY = oldDirX * sin(rotSpeed) + img->dirY * cos(rotSpeed);
		oldPlaneX = img->planeX;
		img->planeX = img->planeX * cos(rotSpeed) - img->planeY * sin(rotSpeed);
		img->planeY = oldPlaneX * sin(rotSpeed) + img->planeY * cos(rotSpeed);
	} // tourne camera gauche
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) // ESC
	{
		mlx_terminate(img->mlx);
		return ;
	}
	*img = raycasting(img->map, *img, *img->cast);
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
	t_cast	cast;

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
	img = raycasting(map, img, cast);
	mlx_key_hook(img.mlx, &moov_camera, &img);
	mlx_key_hook(img.mlx, &moov_player, &img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
