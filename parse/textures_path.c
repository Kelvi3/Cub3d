/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:34:28 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/05 08:37:41 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_path(t_data *map)
{

	//fd = open(map->we, O_RDONLY);
	//printf("map->ea = %s\n", map->ea);
	//printf("fd = %d\n", fd);
	if (access(map->ea, F_OK) == -1)
		return (1);
	if (access(map->ea, F_OK) == -1)
		return (1);
	if (access(map->ea, F_OK) == -1)
		return (1);
	if (access(map->ea, F_OK) == -1)
		return (1);
	if (access(map->ea, F_OK) == -1)
		return (1);
	return (0);
}

int	check_path(t_data *map)
{
	if (!map->ea || !map->no || !map->so || !map->we)
	{
		ft_putstr_fd("Error path\n", 2);
		return (1);
	}
	if (open_path(map) == 1)
	{
		//ft_putstr_fd("Error path\n", 2);
		return (0);
	}
	return (0);
}
