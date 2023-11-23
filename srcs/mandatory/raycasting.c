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
	vector = transf_coord(vector.x, vector.y, vector.z + norm * tan(angle));
	return (vector);
}

/* get case integral coordinates of a point according to a vector */
t_coord	get_case(t_coord vector, t_coord point, int p)
{
	t_coord	_case;

	if (p == NEXT && vector.y > EPSILON)
		_case.y = floor(point.y) + 1;
	if (p == NEXT && vector.y <= EPSILON)
		_case.y = ceil(point.y) - 1;
	if (p == NEXT && vector.x > EPSILON)
		_case.x = floor(point.x) + 1;
	if (p == NEXT && vector.x <= EPSILON)
		_case.x = ceil(point.x) - 1;
	if (p == NEXT && vector.z > EPSILON)
		_case.z = floor(point.z) + 1;
	if (p == NEXT && vector.z <= EPSILON)
		_case.z = ceil(point.z) - 1;
	if (p == CURRENT)
		_case = transf_coord(floor(point.x), floor(point.y), floor(point.z));
	if (p == CURRENT && point.x - round(point.x) < EPSILON && vector.x < 0)
		_case.x = round(point.x - 1);
	if (p == CURRENT && point.y - round(point.y) < EPSILON && vector.y < 0)
		_case.y = round(point.y - 1);
	if (p == CURRENT && point.z - round(point.z) < EPSILON && vector.z < 0)
		_case.z = round(point.z - 1);
	return (_case);
}

/* calculate wall orientation and put the right pixel color 
according to intersection point*/
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
	if (fabs(point.y - get_case(vector, point, CURRENT).y) < EPSILON)
		orientation = 'S';
	else if (fabs(point.y - get_case(vector, point, CURRENT).y - 1) < EPSILON)
		orientation = 'N';
	else if (fabs(point.x - get_case(vector, point, CURRENT).x) < EPSILON)
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
	t_coord		_case;
	t_coord		point;
	double		min;
	static int	count = 0;

	_case = (ft_bzero(&min, sizeof(int)), get_case(vector, start, NEXT));
	if (fabs(vector.x) >= EPSILON)
		min = fabs((_case.x - start.x) / vector.x);
	else if (fabs(vector.y) >= EPSILON)
		min = fabs((_case.y - start.y) / vector.y);
	else if (fabs(vector.z) >= EPSILON)
		min = fabs((_case.z - start.z) / vector.z);
	if (fabs(vector.x) >= EPSILON)
		min = fmin(min, fabs((_case.x - start.x) / vector.x));
	if (fabs(vector.y) >= EPSILON)
		min = fmin(min, fabs((_case.y - start.y) / vector.y));
	if (fabs(vector.z) >= EPSILON)
		min = fmin(min, fabs((_case.z - start.z) / vector.z));
	point = transf_coord(start.x + min * vector.x, start.y + min * vector.y, \
						start.z + min * vector.z);
	_case = get_case(vector, point, CURRENT);
	if (count > 1000 || point.z <= EPSILON || point.z >= 1 - EPSILON || \
		map->tab[(int)(_case.y)][(int)(_case.x)] == 1)
		return (ft_bzero(&count, sizeof(int)), point);
	return (count++, intersection(point, vector, map));
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
}
