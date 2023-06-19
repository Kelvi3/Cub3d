/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:13:18 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 16:17:04 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	not_player(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

int	check_char_player_egal(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	count_size_map(t_data *map, int i)
{
	int	size;

	size = 0;
	while (map->cub[i] && map->cub[i][0] != '\n')
	{
		size++;
		i++;
	}
	return (size);
}

int	size_file_cub(char **argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = 0;
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	i++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}

void	pass_space(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		*i += 1;
}
