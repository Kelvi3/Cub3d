/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:32:15 by lulaens           #+#    #+#             */
/*   Updated: 2023/07/07 18:14:37 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static char	*delete_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] != ' ')
		i++;
	if (str[i] == '\n' || str[i] == ' ')
		str[i] = '\0';
	return (str);
}

static void	copy_no_and_so(t_data *map, int i, int j)
{
	if (map->cub[i][j] == 'N' && map->cub[i][j + 1] \
			&& map->cub[i][j + 1] == 'O')
	{
		j += 2;
		pass_space(map->cub[i], &j);
		map->no = ft_substr(map->cub[i], j, ft_strlen(map->cub[i]));
		map->no = delete_new_line(map->no);
	}
	else if (map->cub[i][j] == 'S' && map->cub[i][j + 1] \
			&& map->cub[i][j + 1] == 'O')
	{
		j += 2;
		pass_space(map->cub[i], &j);
		map->so = ft_substr(map->cub[i], j, ft_strlen(map->cub[i]));
		map->so = delete_new_line(map->so);
	}
}

static void	copy_we_and_ea(t_data *map, int i, int j)
{
	if (map->cub[i][j] == 'W' && map->cub[i][j + 1] \
			&& map->cub[i][j + 1] == 'E')
	{
		j += 2;
		pass_space(map->cub[i], &j);
		map->we = ft_substr(map->cub[i], j, ft_strlen(map->cub[i]));
		map->we = delete_new_line(map->we);
	}
	else if (map->cub[i][j] == 'E' && map->cub[i][j + 1] \
		&& map->cub[i][j + 1] == 'A')
	{
		j += 2;
		pass_space(map->cub[i], &j);
		map->ea = ft_substr(map->cub[i], j, ft_strlen(map->cub[i]));
		map->ea = delete_new_line(map->ea);
	}
}

static void	copy_path_texture(t_data *map, int i, int j)
{
	copy_no_and_so(map, i, j);
	copy_we_and_ea(map, i, j);
}

void	add_path_texture(t_data *map)
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
			copy_path_texture(map, i, j);
		}
		if (map->no && map->so && map->we && map->ea)
			break ;
		i++;
	}
}
