/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:13:17 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/09 14:17:34 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_value_data(int argc, t_data *map)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		exit (1);
	}
	map->color_c = NULL;
	map->color_f = NULL;
	map->cub = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
}

int	parse(t_data *map)
{
	if (copy_map(map) == 1)
		return (1);
	add_path_texture(map);
	add_color(map);
	if (check_color(map->color_f) || check_color(map->color_c) \
			|| add_color_in_tab_f(map) || add_color_in_tab_c(map) \
			|| check_len_int_tab(map->colorc) || check_len_int_tab(map->colorf) \
			|| check_char_in_map(map) || check_map(map) || check_path(map))
		return (1);
	return (0);
}
