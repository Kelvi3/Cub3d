/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cube_and_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:42:13 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 16:58:15 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	size_zero_exit(t_data *map)
{
	ft_putstr_fd("Error\n", 2);
	free_all(map);
	exit(1);
}

void	add_all_cube(char **argv, t_data *map)
{
	int		i;
	int		size;
	int		fd;

	i = 0;
	size = 0;
	fd = open(argv[1], O_RDONLY);
	size = size_file_cub(argv);
	if (size == 1)
		size_zero_exit(map);
	map->cub = malloc(sizeof(char *) * size);
	if (!map->cub)
		return ;
	map->cub[i] = get_next_line(fd);
	if (map->cub[i] == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return ;
	}
	while (map->cub[i])
	{
		i++;
		map->cub[i] = get_next_line(fd);
	}
	close(fd);
}

static void	search_index_map(t_data *map, int *i)
{
	int	count;

	count = 0;
	while (map->cub[*i])
	{
		if (count == 6)
			break ;
		if (map->cub[*i] && map->cub[*i][0] != '\n' && map->cub[*i][1] != '\0')
			count++;
		*i += 1;
	}
	while (map->cub[*i] && map->cub[*i][0] == '\n' && map->cub[*i][1] == '\0')
		*i += 1;
}

int	check_end_cub(t_data *map, int i)
{
	if (map->cub[i])
	{
		while (map->cub[i])
		{
			if (map->cub[i][0] != '\n')
			{
				ft_putstr_fd("Error\n", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	copy_map(t_data *map)
{
	int	i;
	int	z;
	int	size;

	i = 0;
	z = 0;
	search_index_map(map, &i);
	size = count_size_map(map, i);
	map->map = ft_calloc(sizeof(char *), (size + 1));
	if (!map->map)
		return (1);
	while (map->cub[i] && z < size)
	{
		map->map[z] = ft_strdup(map->cub[i]);
		z++;
		i++;
	}
	if (check_end_cub(map, i) == 1)
		return (1);
	return (0);
}
