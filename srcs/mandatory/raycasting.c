/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:55:48 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/04 15:55:53 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* changes pixel coordinates into 3 dimensional coordinates */
t_coord	get_vector(t_img_data *canvas, int j, int i, t_cubdata *cub)
{
	double	alpha;
	double	beta;
	t_point	crosshair;
	t_coord	vector;

	crosshair.x = canvas->width * RATIOHOR;
	crosshair.y = canvas->height * RATIOVER;
	alpha = (j - crosshair.x) * cub->settings.fov / canvas->width;
	beta = (i - crosshair.y) * cub->settings.fov / canvas->width;
	vector.x = cub->player.direction.x * cos(alpha) + \
				cub->player.direction.y * sin(alpha);
	vector.y = -cub->player.direction.x * sin(alpha) + \
				cub->player.direction.y * cos(alpha);
	vector.z = cub->player.direction.z;
	vector.x = vector.x * cos(beta) - vector.z * sin(beta);
	vector.z = vector.x * sin(beta) + vector.z * cos(beta);
	return (vector);
}

void	raycasting_put(t_coord point, t_cubdata *cub, int x, int y)
{
	t_img_data	*canvas;
	int			i;
	int			j;
	t_img_data	*img;
	char		orientation;

	canvas = get_canvas(&cub->data, MAIN);
	if (point.z == 0)
		return (my_mlx_pixel_put(canvas, x, y, cub->f_color));
	if (point.z == 1)
		return (my_mlx_pixel_put(canvas, x, y, cub->c_color));
	if (point.y == y)
		orientation = 'S';
	if (point.y == y + 1)
		orientation = 'N';
	if (point.x == x)
		orientation = 'E';
	if (point.x == x + 1)
		orientation = 'W';
	img = new_image(&cub->data, orientation, NULL, NULL);
	i = (point.z - floor(point.z)) * img->height;
	j = (point.x - floor(point.x)) * img->width;
	if (point.x == (int)(point.x))
		j = (point.y - floor(point.y)) * img->width;
	my_mlx_pixel_put(canvas, x, y, img->addr[i * img->height + j]);
}

t_coord	get_integral(t_coord vector, t_coord point)
{
	t_coord	integral;

	if (vector.y > 0)
		integral.y = floor(point.y) + 1;
	else
		integral.y = ceil(point.y) - 1;
	if (vector.x > 0)
		integral.x = floor(point.x) + 1;
	else
		integral.x = ceil(point.x) - 1;
	if (vector.z > 0)
		integral.z = floor(point.z) + 1;
	else
		integral.z = ceil(point.z) - 1;
	return (integral);
}

/* returns coordinates of the intersection between vector and a wall */
t_coord	intersection(t_coord start, t_coord vector, t_map *map)
{
	t_coord	integral;
	t_coord	point;
	double	min;

	integral = get_integral(vector, start);
	if (vector.x != 0)
		min = (integral.x - start.x) / vector.x;
	else if (vector.y != 0)
		min = (integral.y - start.y) / vector.y;
	else if (vector.z != 0)
		min = (integral.z - start.z) / vector.z;
	if (vector.x != 0)
		min = fmin(min, (integral.x - start.x) / vector.x);
	if (vector.y != 0)
		min = fmin(min, (integral.y - start.y) / vector.y);
	if (vector.z != 0)
		min = fmin(min, (integral.z - start.z) / vector.z);
	point = transf_coord(start.x + min * vector.x, start.y + min * vector.y, \
						start.z + min * vector.z);
	integral = get_integral(vector, point);
	if (point.z == 0 || point.z == 1 || map->tab[integral.y][integral.x])
		return (point);
	return (intersection(point, vector, map));
}

/* go through every pixel of the screen and apply raycasting method */
void	raycasting(t_cubdata *cub)
{
	t_data		*data;
	t_img_data	*canvas;
	int			i;
	int			j;

	i = 0;
	data = &cub->data;
	canvas = get_canvas(data, MAIN);
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			raycasting_put(intersection(cub->player.position, \
			get_vector(canvas, j, i, cub), &cub->map), cub, j, i);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win.ptr, canvas->ptr, 0, 0);
}
