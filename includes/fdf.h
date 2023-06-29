/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:08:15 by zrebhi            #+#    #+#             */
/*   Updated: 2023/01/02 11:40:50 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  FDF_H
# define FDF_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 5000
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1500
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

/* utils */

typedef struct s_map
{
	int		xmax;
	int		ymax;
	int		**tab;

	int		zoom;
	int		color;
	int		iso;
	int		z_coef;
	int		shift_x;
	int		shift_y;
	float	angle_x;
	float	angle_y;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

typedef struct s_floats
{
	float	x;
	float	x1;
	float	y;
	float	y1;
}			t_floats;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);

size_t	ft_linelen(const char *line);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char *s1, char *s2);

char	**ft_split(char const *s, char c);

int		ft_words(char const *s, char c);

/* parsing */

void	ft_parsing(char *file, t_fdf *tab);

/* draw */

void	bresenham(t_floats points, t_fdf *tab);

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color);

void	ft_drawmap(t_fdf *tab);

/* view */

void	isometric(t_floats *points, t_fdf *tab, int z, int z1);

void	shift(t_floats *points, t_fdf *tab);

void	zoom(t_floats *points, t_fdf *tab);

void	color(t_fdf *tab, int z, int z1);

void	view_init(t_fdf *tab);

int		hooks(int key, t_fdf *tab);

int		killfile(t_fdf *tab);

#endif