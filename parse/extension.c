/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:25:18 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 14:26:04 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_extension(char *str, char *ext)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	j = 0;
	while (str[i] != '.')
		i++;
	if (str[i] == ext[j])
	{
		while ((str[i] == ext[j]) && str[i] && ext[j])
		{
			c++;
			i++;
			j++;
		}
	}
	if (c != 4 || str[i] != '\0')
	{
		ft_putstr_fd("Error extension\n", 2);
		exit (1);
	}
}
