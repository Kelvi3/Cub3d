/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:05:53 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 16:42:02 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
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
