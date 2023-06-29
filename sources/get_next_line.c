/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:36:10 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/23 15:20:04 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* Reads the file and adds BUFFER_SIZE bytes to our cache until it contains a 
'\n'. We initialize readlen at symbolic value 42 to get into the while 
on function call */

static char	*ft_read_line(int fd, char *cache)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readlen;

	readlen = 42;
	while (readlen != 0 && !ft_strchr(cache, '\n'))
	{
		readlen = read(fd, buffer, BUFFER_SIZE);
		if (readlen == -1)
			return (free(cache), NULL);
		buffer[readlen] = 0;
		cache = ft_strjoin(cache, buffer);
		if (!cache)
			return (0);
	}
	return (cache);
}

/* Returns the cache before the first \n (if any), essentially our new line */

static char	*ft_new_line(char *cache)
{
	char	*new_line;
	int		i;

	if (cache[0] == 0)
		return (0);
	new_line = malloc(sizeof(char) * (ft_linelen(cache) + 1));
	if (!new_line)
		return (0);
	i = 0;
	while (cache[i] && cache[i] != '\n')
	{
		new_line[i] = cache[i];
		i++;
	}
	if (cache[i] == '\n')
	{
		new_line[i] = cache[i];
		i++;
	}
	new_line[i] = 0;
	return (new_line);
}

/* Returns the cache after the first \n (if any),
this is our new cache for future function calls */

static char	*ft_after_line(char *cache)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!cache)
		return (0);
	while (cache[i] && cache[i] != '\n')
		i++;
	if (!cache[i])
		return (free(cache), NULL);
	i++;
	str = malloc(sizeof(char) * (ft_strlen(cache) - i + 1));
	if (!str)
		return (0);
	while (cache[i])
		str[j++] = cache[i++];
	str[j] = 0;
	return (free(cache), str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*cache;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	cache = ft_read_line(fd, cache);
	if (!cache)
		return (free(cache), NULL);
	line = ft_new_line(cache);
	cache = ft_after_line(cache);
	return (line);
}
