/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:37:03 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/28 16:49:10 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\n'))
			i++;
		if (s[i] != c && s[i] != 0 && s[i] != '\n')
		{
			words++;
			i++;
		}
		while (s[i] && (s[i] != c))
			i++;
	}
	return (words);
}

static char	*ft_dupstr(char const *s, int i, int j)
{
	char	*dup;
	int		x;

	dup = malloc(sizeof(char) * (j - i + 1));
	if (!dup)
		return (0);
	x = 0;
	while (s[i] && i < j)
	{
		dup[x] = s[i];
		x++;
		i++;
	}
	dup[x] = 0;
	return (dup);
}

static char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static	char	**ft_lines(char const *s, char c, char **strs, int x)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\n'))
			i++;
		j = i;
		while (s[j] && s[j] != c && s[j] != '\n')
			j++;
		if (s[j] == c || s[j] == '\n'
			|| (!s[j] && s[j - 1] != c && s[j - 1] != '\n'))
		{
			strs[x] = ft_dupstr(s, i, j);
			if (strs[x] == 0)
				return (ft_free(strs));
			x++;
			i = j;
		}
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	strs = malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!strs)
		return (NULL);
	strs = ft_lines(s, c, strs, 0);
	if (strs)
		strs[ft_words(s, c)] = 0;
	return (strs);
}
