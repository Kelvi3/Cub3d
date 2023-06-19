/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:18:03 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 15:09:15 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	check_zero(t_data *map, int i, int j)
{
	if (map->map[i][j + 1] != '1' && map->map[i][j + 1] != '0' \
			&& not_player(map->map[i][j + 1]))
		return (1);
	if (j > 0 && map->map[i][j - 1] != '1' && map->map[i][j - 1] != '0' \
			&& not_player(map->map[i][j - 1]))
		return (1);
	if (map->map[i + 1][j] != '1' && map->map[i + 1][j] != '0' \
			&& not_player(map->map[i + 1][j]))
		return (1);
	if (i > 0 && map->map[i - 1][j] != '1' && map->map[i - 1][j] != '0' \
			&& not_player(map->map[i - 1][j]))
		return (1);
	return (0);
}

static int	check_zero_one(t_data *map, int i, int j)
{
	if (map->map[i][j + 1] != '1' && map->map[i][j + 1] != '0')
		return (1);
	if (j > 0 && map->map[i][j - 1] != '1' && map->map[i][j - 1] != '0')
		return (1);
	if (map->map[i + 1][j] != '1' && map->map[i + 1][j] != '0')
		return (1);
	if (i > 0 && map->map[i - 1][j] != '1' && map->map[i - 1][j] != '0')
		return (1);
	return (0);
}

int	check_case_map(t_data *map, int i, int j)
{
	if (map->map[i][j] == '0')
	{
		if (check_zero(map, i, j) == 1)
		{
			ft_putstr_fd("Error map open\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_map(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (check_case_map(map, i, j) == 1)
				return (1);
			if (check_char_player_egal(map->map[i][j]) == 1)
			{
				if (check_zero_one(map, i, j) == 1)
				{
					ft_putstr_fd("Error map open\n", 2);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
