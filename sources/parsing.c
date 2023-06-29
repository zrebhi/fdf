/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:10:52 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/28 15:39:35 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* Finds out the size of our tab so we can malloc it accordingly */

static void	ft_size(t_fdf *tab, int fd)
{
	char				*str;
	int					i;

	tab->xmax = 0;
	tab->ymax = 1;
	str = get_next_line(fd);
	if (!str)
		exit (0);
	tab->xmax = ft_words(str, ' ');
	free(str);
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		free(str);
		if (!str)
			break ;
		tab->ymax++;
	}
}

static void	ft_malloc_tab(t_fdf *tab)
{
	int	i;

	tab->tab = malloc(sizeof(int *) * (tab->xmax));
	if (!tab->tab)
		return (free(tab), exit (0));
	i = 0;
	while (i < tab->xmax)
	{
		tab->tab[i] = malloc(sizeof(int) * (tab->ymax));
		if (!tab->tab[i])
			killfile(tab);
		i++;
	}
}

/* Creates a table of ints from a map file. 
It is set up so that tab[x][y] = z where x and y are the horizontal and
vertical coordinates of our points and z their altitude. */

static void	ft_mapping(t_fdf *tab, int fd)
{
	int		x;
	int		y;
	int		i;
	char	*str;
	char	**strs;

	y = 0;
	while (y < tab->ymax)
	{
		str = get_next_line(fd);
		if (!str)
			killfile(tab);
		i = 0;
		x = 0;
		strs = ft_split(str, ' ');
		free (str);
		while (strs[i])
		{
			tab->tab[x++][y] = ft_atoi(strs[i]);
			free(strs[i++]);
		}
		free(strs);
		y++;
	}
}

/* Wraps everything above in a single function */

void	ft_parsing(char *file, t_fdf *tab)
{
	int		fd;

	fd = open(file, O_RDONLY);
	ft_size(tab, fd);
	close(fd);
	ft_malloc_tab(tab);
	fd = open(file, O_RDONLY);
	ft_mapping(tab, fd);
	close(fd);
}
