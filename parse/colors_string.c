/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:43:15 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 14:53:50 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	not_number_and_mark(char *color, int i)
{
	i = 0;
	while (color[i] && color[i] != '\n')
	{
		if ((color[i] < '0' || color[i] > '9') \
				&& color[i] != ',')
		{
			ft_putstr_fd("Error parse color\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_color(char *color)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!color)
		return (0);
	while (color[i])
	{
		if (color[i] == ',')
			c++;
		i++;
	}
	if (c != 2)
	{
		ft_putstr_fd("Error parse color\n", 2);
		return (1);
	}
	if (not_number_and_mark(color, i) == 1)
		return (1);
	return (0);
}

static void	copy_color(t_data *map, int i, int *j)
{
	if (map->cub[i][*j] == 'F' && !map->color_f)
	{
		*j += 1;
		pass_space(map->cub[i], j);
		map->color_f = ft_substr(map->cub[i], *j, ft_strlen(map->cub[i]));
	}
	else if (map->cub[i][*j] == 'C' && !map->color_c)
	{
		*j += 1;
		pass_space(map->cub[i], j);
		map->color_c = ft_substr(map->cub[i], *j, ft_strlen(map->cub[i]));
	}
}

void	add_color(t_data *map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map->cub[i])
	{
		j = 0;
		if (map->cub[i][0] != '\n')
		{
			pass_space(map->cub[i], &j);
			copy_color(map, i, &j);
		}
		i++;
	}
}
