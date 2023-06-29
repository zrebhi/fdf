/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:45:55 by zrebhi            #+#    #+#             */
/*   Updated: 2022/12/27 15:04:34 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	max1(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	mod(float index)
{
	if (index < 0)
		return (-index);
	else
		return (index);
}

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x <= 0 || y <= 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	bresenham(t_floats points, t_fdf *tab)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;

	z = tab->tab[(int)points.x][(int)points.y] * tab->z_coef;
	z1 = tab->tab[(int)points.x1][(int)points.y1] * tab -> z_coef;
	zoom(&points, tab);
	color(tab, z, z1);
	if (tab->iso == 1)
		isometric(&points, tab, z, z1);
	shift(&points, tab);
	x_step = points.x1 - points.x;
	y_step = points.y1 - points.y;
	max = max1(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(points.x - points.x1) || (int)(points.y - points.y1))
	{
		my_mlx_pixel_put(tab, points.x, points.y, tab->color);
		points.x += x_step;
		points.y += y_step;
	}
}

void	ft_drawmap(t_fdf *tab)
{
	t_floats	points;

	points.y = 0;
	while (points.y < tab->ymax)
	{
		points.x = 0;
		while (points.x < tab->xmax)
		{
			if (points.x < tab->xmax - 1)
			{
				points.x1 = (points.x) + 1;
				points.y1 = points.y;
				bresenham(points, tab);
			}
			if (points.y < tab->ymax - 1)
			{
				points.x1 = points.x;
				points.y1 = points.y + 1;
				bresenham(points, tab);
			}
			points.x++;
		}
		points.y++;
	}
}
