/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:19:10 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/27 15:34:42 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	shift_key(int key, t_fdf *tab)
{
	if (key == 126)
		tab->shift_y -= 50;
	if (key == 125)
		tab->shift_y += 50;
	if (key == 123)
		tab->shift_x -= 50;
	if (key == 124)
		tab->shift_x += 50;
	mlx_destroy_image(tab->mlx_ptr, tab->img);
	tab->img = mlx_new_image(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	tab->addr = mlx_get_data_addr(tab->img, &tab->bits_per_pixel,
			&tab->line_length, &tab->endian);
	ft_drawmap(tab);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	return (0);
}

int	rotate_key(int key, t_fdf *tab)
{
	if (key == 13)
		tab->angle_y -= 0.2;
	if (key == 1)
		tab->angle_y += 0.2;
	if (key == 0)
		tab->angle_x -= 0.2;
	if (key == 2)
		tab->angle_x += 0.2;
	mlx_destroy_image(tab->mlx_ptr, tab->img);
	tab->img = mlx_new_image(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	tab->addr = mlx_get_data_addr(tab->img, &tab->bits_per_pixel,
			&tab->line_length, &tab->endian);
	ft_drawmap(tab);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	return (0);
}

int	zoom_key(int key, t_fdf *tab)
{
	if (key == 78)
		tab->zoom -= 2;
	if (key == 69)
		tab->zoom += 2;
	mlx_destroy_image(tab->mlx_ptr, tab->img);
	tab->img = mlx_new_image(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	tab->addr = mlx_get_data_addr(tab->img, &tab->bits_per_pixel,
			&tab->line_length, &tab->endian);
	ft_drawmap(tab);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	return (0);
}

int	iso_key(int key, t_fdf *tab)
{
	if (key == 49)
	{
		if (tab->iso == 1)
			tab->iso = 0;
		else
			tab->iso = 1;
	}
	if (key == 116)
		tab->z_coef += 1;
	if (key == 121)
		tab->z_coef -= 1;
	mlx_destroy_image(tab->mlx_ptr, tab->img);
	tab->img = mlx_new_image(tab->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	tab->addr = mlx_get_data_addr(tab->img, &tab->bits_per_pixel,
			&tab->line_length, &tab->endian);
	ft_drawmap(tab);
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	return (0);
}

int	hooks(int key, t_fdf *tab)
{
	if (key == 13 || key == 0 || key == 1 || key == 2)
		rotate_key(key, tab);
	if (key == 126 || key == 125 || key == 124 || key == 123)
		shift_key(key, tab);
	if (key == 69 || key == 78)
		zoom_key(key, tab);
	if (key == 49 || key == 116 || key == 121)
		iso_key(key, tab);
	if (key == 53)
		killfile(tab);
	return (0);
}
