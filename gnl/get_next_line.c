/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulaens <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:17:52 by lulaens           #+#    #+#             */
/*   Updated: 2023/06/19 15:12:17 by lulaens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*ft_readfile(int fd, char *buf)
{
	int		i;
	char	*str;

	if (!buf)
		buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	str = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	i = 1;
	while (i > 0 && !(ft_strchr(str, '\n')))
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1 || (i == 0 && buf[0] == '\0'))
		{
			free(buf);
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		buf = ft_strjoin(buf, str);
	}
	free(str);
	return (buf);
}

char	*ft_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (buf[i] == '\0')
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	while (buf[i] == '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n' && buf[i])
		line[i++] = '\n';
	return (line);
}

char	*ft_nextline(char *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (ft_strlen(buf) - i) + 1);
	if (!line)
		return (NULL);
	if (buf[i])
		i++;
	while (buf[i])
		line[j++] = buf[i++];
	if (line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_readfile(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_line(buf);
	buf = ft_nextline(buf);
	return (line);
}
