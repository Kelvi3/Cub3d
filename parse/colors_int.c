/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:43:27 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/08 16:57:50 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	len_double_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	add_color_in_tab_f(t_data *map)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(map->color_f, ',');
	if (!tmp || len_double_tab(tmp) != 3)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	while (tmp[i])
	{
		map->colorf[i] = ft_atoi(tmp[i]);
		i++;
	}
	free_tab(tmp);
	return (0);
}

int	add_color_in_tab_c(t_data *map)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(map->color_c, ',');
	if (!tmp)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	while (tmp[i])
	{
		map->colorc[i] = ft_atoi(tmp[i]);
		i++;
	}
	free_tab(tmp);
	return (0);
}

int	check_len_int_tab(int tab[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (tab[i] > 255 || tab[i] < 0)
		{
			ft_putstr_fd("Error\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
