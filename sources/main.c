/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:47:52 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/28 15:16:30 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/fdf.h"

int	killfile(t_fdf *tab)
{
	int	x;

	mlx_destroy_window(tab->mlx_ptr, tab->win_ptr);
	x = 0;
	while (x < tab->xmax && tab->tab[x] != 0)
	{
		free(tab->tab[x]);
		x++;
	}
	free(tab->tab);
	free(tab);
	exit (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*tab;

	if (argc != 2)
		return (0);
	tab = (t_fdf *)malloc(sizeof(t_fdf));
	if (!tab)
		exit (0);
	ft_parsing(argv[1], tab);
	tab->mlx_ptr = mlx_init();
	tab->win_ptr = mlx_new_window(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	tab->img = mlx_new_image(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	tab->addr = mlx_get_data_addr(tab->img, &tab->bits_per_pixel,
			&tab->line_length, &tab->endian);
	view_init(tab);
	ft_drawmap(tab);
	mlx_hook(tab->win_ptr, 17, 1l << 0, killfile, tab);
	mlx_key_hook(tab->win_ptr, hooks, tab);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	mlx_loop(tab->mlx_ptr);
}
