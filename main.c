/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:22 by tcazenav          #+#    #+#             */
/*   Updated: 2023/07/08 13:56:55 by tcazenav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "cub3D.h"

t_map	player_view(t_map img, char c)
{
	if (c == 'S')
	{
		img.dirX = 1.0;
		img.planeY = 0.66;
	}
	if (c == 'N')
	{
		img.dirX = -1.0;
		img.planeY = -0.66;
	}
	if (c == 'W')
	{
		img.dirY = 1.0;
		img.planeX = -0.66;
	}
	if (c == 'E')
	{
		img.dirY = -1.0;
		img.planeX = 0.66;
	}
	return (img);
}

t_map	get_pos_player(t_data map, t_map img)
{
	int	i;
	int	j;

	i = 0;
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
				img = player_view(img, map.map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (img);
}

t_map	load_image(t_data map, t_map img)
{
	img = get_pos_player(map, img);
	img.texture_n = mlx_load_png(map.no);
	img.texture_s = mlx_load_png(map.so);
	img.texture_e = mlx_load_png(map.ea);
	img.texture_w = mlx_load_png(map.we);
	img.image = mlx_new_image(img.mlx, 1280, 720);
	img = raycasting(map, img, img.cast);
	return (img);
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
		free_all(&map);
		return (1);
	}
	img.mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!img.mlx)
		return (2);
	img.map = map;
	img = load_image(map, img);
	mlx_loop_hook(img.mlx, moov_player, &img);
	mlx_loop(img.mlx);
	mlx_delete_image(img.mlx, img.image);
	free_all(&map);
	return (0);
}
