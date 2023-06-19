/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:36:01 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 15:17:13 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	case_in_map(t_data *map, int i, int j)
{
	if (map->map[i][j] != '1' && map->map[i][j] != '0' \
			&& map->map[i][j] != ' ' && map->map[i][j] != '	' \
			&& map->map[i][j] != '\n' \
			&& not_player(map->map[i][j]))
	{
		ft_putstr_fd("Error in map\n", 2);
		return (1);
	}
	return (0);
}

static int	count_nb_player(int c)
{
	if (c > 1 || c < 1)
	{
		ft_putstr_fd("Error player\n", 2);
		return (1);
	}
	return (0);
}

int	check_char_in_map(t_data *map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (case_in_map(map, i, j))
				return (1);
			if (check_char_player_egal(map->map[i][j]))
				c++;
			j++;
		}
		i++;
	}
	if (count_nb_player(c) == 1)
		return (1);
	return (0);
}
