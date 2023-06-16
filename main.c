#include "cub3D.h"

int	parse(t_data *map)
{
	if (copy_map(map) == 1)
		return (1);
	add_path_texture(map);
	add_color(map);
	if (check_color(map->color_f) || check_color(map->color_c))
		return (1);
	if (add_color_in_tab_f(map) == 1)
		return (1);
	if (add_color_in_tab_c(map) == 1)
		return (1);
	if (check_len_int_tab(map->colorc) == 1)
		return (1);
	if (check_len_int_tab(map->colorf) == 1)
		return (1);
	if (check_char_in_map(map) == 1)
		return (1);
	if (check_map(map) == 1)
		return (1);
	return (0);
}

void	free_all(t_data *map)
{
	if (map->cub)
		free_tab(map->cub);
	if (map->map)
		free_tab(map->map);
	if (map->ea)
		free(map->ea);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->color_c)
		free(map->color_c);
	if (map->color_f)
		free(map->color_f);
}


void	init_value_data(t_data *map)
{
	map->color_c = NULL;
	map->color_f = NULL;
	map->cub = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
}

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

/* - parse player si il est face au vide
 * - mettre tout les lignes de la map au meme niveau que la plus grande
 * avec des espace 
 * - check la taille des int > 255 pour les couleurs 
 * - check si les path des textures sont bons */

int	main(int argc, char **argv)
{
	t_data	map;
	
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
	free_all(&map);
	return (0);
}
