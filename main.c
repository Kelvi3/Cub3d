/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcazenav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:22 by tcazenav          #+#    #+#             */
/*   Updated: 2023/07/08 16:26:04 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "cub3D.h"

t_map	player_view(t_map img, char c)
{
	if (c == 'S')
	{
		img.dir_x = 1.0;
		img.plane_y = -0.66;
	}
	if (c == 'N')
	{
		img.dir_x = -1.0;
		img.plane_y = 0.66;
	}
	if (c == 'E')
	{
		img.dir_y = 1.0;
		img.plane_x = 0.66;
	}
	if (c == 'W')
	{
		img.dir_y = -1.0;
		img.plane_x = -0.66;
	}
	return (img);
}

t_map	get_pos_player(t_data map, t_map img)
{
	int	i;
	int	j;

	i = 0;
	img.dir_x = 0.0;
	img.dir_y = 0.0;
	img.plane_x = 0.0;
	img.plane_y = 0.0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j] != '\0' && map.map[i][j] != '\n')
		{
			if (map.map[i][j] == 'E' || map.map[i][j] == 'W'
				|| map.map[i][j] == 'S' || map.map[i][j] == 'N')
			{
				img.pos_x = (double)i + 0.5;
				img.pos_y = (double)j + 0.5;
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
	return (img);
}

int	main(int argc, char **argv)
{
	t_data	map;
	t_map	img;

	if (argc != 2)
		ft_putstr_fd("Error arg\n", 2);
	if (argc != 2)
		return (1);
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
	img.image = mlx_new_image(img.mlx, 1280, 720);
	img = load_image(map, img);
	img = raycasting(map, img, img.cast);
	mlx_loop_hook(img.mlx, moov_player, &img);
	mlx_loop(img.mlx);
	free_all(&map);
	return (0);
}
