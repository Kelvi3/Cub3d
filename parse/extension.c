/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:25:18 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/20 12:07:58 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	check_path_map(char *str)
{
	if (open(str, O_RDONLY) == -1)
	{
		ft_putstr_fd("Error file\n", 2);
		exit (1);
	}
}

void	check_extension(char *str, char *ext)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	c = 0;
	check_path_map(str);
	while (str[i + 1])
		i++;
	while (str[i] && str[i] != '.')
		i--;
	while ((str[i] == ext[j]) && str[i] && ext[j])
	{
		c++;
		i++;
		j++;
	}
	if (c != 4 || str[i] != '\0')
	{
		ft_putstr_fd("Error ext\n", 2);
		exit (1);
	}
}
