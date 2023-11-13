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
	double	angle;
	double	norm;
	t_coord	cam;
	t_coord	vector;

	cam = transf_coord(canvas->width * RATIOH, canvas->height * RATIOV, 0);
	angle = (j - cam.x) * cub->settings.fov * M_PI / (canvas->width * 180);
	vector.x = cub->player.direction.x * cos(angle) - \
				cub->player.direction.y * sin(angle);
	vector.y = cub->player.direction.x * sin(angle) + \
				cub->player.direction.y * cos(angle);
	vector.z = cub->player.direction.z;
	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	angle = (cam.y - i) * cub->settings.fov * M_PI / (canvas->width * 180);
	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	vector = transf_coord(vector.x, vector.y, vector.z + norm * tan(angle));
	return (vector);
}

/* t_coord	get_case(t_coord vector, t_coord point)
{
	t_coord	_case;

	_case = transf_coord(floor(point.x), floor(point.y), floor(point.z));
	if (point.x - floor(point.x) < EPSILON && vector.x < 0)
		_case.x = floor(point.x) - 1;
	if (point.y - floor(point.y) < EPSILON && vector.y < 0)
		_case.y = floor(point.y) - 1;
	if (point.z - floor(point.z) < EPSILON && vector.z < 0)
		_case.z = floor(point.z) - 1;
	return (_case);
} */

t_coord	get_case(t_coord vector, t_coord point)
{
	t_coord	_case;

	if (vector.y > 0)
		_case.y = floor(point.y) + 1;
	else
		_case.y = ceil(point.y) - 1;
	if (vector.x > 0)
		_case.x = floor(point.x) + 1;
	else
		_case.x = ceil(point.x) - 1;
	if (vector.z > 0)
		_case.z = floor(point.z) + 1;
	else
		_case.z = ceil(point.z) - 1;
	return (_case);
}

void	raycasting_put(t_coord point, t_cubdata *cub, t_point p, t_coord vector)
{
	t_img_data	*canvas;
	int			i;
	int			j;
	t_img_data	*img;
	char		orientation;

	canvas = get_canvas(&cub->data, MAIN);
	if (point.z <= EPSILON)
		return (my_mlx_pixel_put(canvas, p.x, p.y, cub->f_color));
	if (point.z >= 1 - EPSILON)
		return (my_mlx_pixel_put(canvas, p.x, p.y, cub->c_color));
	if (fabs(point.y + 1 - get_case(vector, point).y) < EPSILON)
		orientation = 'S';
	else if (fabs(point.y - get_case(vector, point).y - 1) < EPSILON)
		orientation = 'N';
	else if (fabs(point.x + 1 - get_case(vector, point).x) < EPSILON)
		orientation = 'E';
	else
		orientation = 'W';
	img = new_image(&cub->data, orientation, NULL, NULL);
	i = (point.z - floor(point.z)) * img->height;
	j = (point.x - floor(point.x)) * img->width;
	if (point.x == (int)(point.x))
		j = (point.y - floor(point.y)) * img->width;
	my_mlx_pixel_put(canvas, p.x, p.y, ((int *)img->addr)[i * img->height + j]);
}

/* returns coordinates of the intersection between vector and a wall */
t_coord	intersection(t_coord start, t_coord vector, t_map *map)
{
	t_coord	_case;
	t_coord	point;
	double	min;

	_case = get_case(vector, start);
	if (vector.x != 0)
		min = (_case.x - start.x) / vector.x;
	else if (vector.y != 0)
		min = (_case.y - start.y) / vector.y;
	else if (vector.z != 0)
		min = (_case.z - start.z) / vector.z;
	if (vector.x != 0)
		min = fmin(min, (_case.x - start.x) / vector.x);
	if (vector.y != 0)
		min = fmin(min, (_case.y - start.y) / vector.y);
	if (vector.z != 0)
		min = fmin(min, (_case.z - start.z) / vector.z);
	point = transf_coord(start.x + min * vector.x, start.y + min * vector.y, \
						start.z + min * vector.z);
	_case = get_case(vector, point);
	if (point.z <= EPSILON || point.z >= 1 - EPSILON || \
		map->tab[(int)_case.y][(int)_case.x] == 1)
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
	t_coord		vector;

	i = 0;
	data = &cub->data;
	canvas = get_canvas(data, MAIN);
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			vector = get_vector(canvas, j, i, cub);
			raycasting_put(intersection(cub->player.position, \
			vector, &cub->map), cub, transf_point(j, i), vector);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win.ptr, canvas->ptr, 0, 0);
	printf("\n");
}
