/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:22:33 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/28 16:54:51 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	view_init(t_fdf *tab)
{
	tab->angle_x = 0.8;
	tab->angle_y = 0.8;
	tab->shift_x = 800;
	tab->shift_x = 800;
	tab->zoom = 1;
	tab->iso = 1;
	tab->z_coef = 1;
}

void	isometric(t_floats *points, t_fdf *tab, int z, int z1)
{
	points->x = (points->x - points->y) * cos(tab->angle_x);
	points->y = (points->x + points->y) * sin(tab->angle_y) - z;
	points->x1 = (points->x1 - points->y1) * cos(tab->angle_x);
	points->y1 = (points->x1 + points->y1) * sin(tab->angle_y) - z1;
}

void	shift(t_floats *points, t_fdf *tab)
{
	points->x += tab->shift_x;
	points->x1 += tab->shift_x;
	points->y += tab->shift_y;
	points->y1 += tab->shift_y;
}

void	zoom(t_floats *points, t_fdf *tab)
{
	points->x *= tab->zoom;
	points->x1 *= tab->zoom;
	points->y *= tab->zoom;
	points->y1 *= tab->zoom;
}

void	color(t_fdf *tab, int z, int z1)
{
	if (z > 0 || z1 > 0)
		tab->color = 0xE80C0C;
	else
		tab->color = 0xFFFFFF;
}
