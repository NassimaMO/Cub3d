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
	double	angle_ver;
	double	angle_hor;
	double	norm;
	t_coord	cam;
	t_coord	vector;
	t_coord	axis;

	cam = transf_coord(canvas->width / 2.0, canvas->height / 2.0, 0);
	angle_hor = (j - cam.x) * cub->settings.fov * M_PI / (canvas->width * 180);
	vector.x = cub->player.direction.x * cos(angle_hor) - \
				cub->player.direction.y * sin(angle_hor);
	vector.y = cub->player.direction.x * sin(angle_hor) + \
				cub->player.direction.y * cos(angle_hor);
	vector.z = cub->player.direction.z;
	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	/* VECTOR NORMALIZATION */
	/* vector.x /= norm;
	vector.y /= norm;
	vector.z /= norm; */

	/* PREVIOUS ANGLE CALCULATION */
	//angle_ver = (cam.y - i) * cub->settings.fov * M_PI / (canvas->width * 180);

	/* NEW ANGLE CALCULATION */
	angle_ver = atan((cam.y - i) * cos(angle_hor) * 2 * tan(cub->settings.fov / 2) / canvas->width);
	
	/* VECTOR COORDINATES VERSION 1 : CHANGE OF Z COMPONANT (VECTOR NO LONGER NORMALIZED) */
	vector.z += norm * tan(angle_ver);

	/* VECTOR COORDINATES VERSION 2 : ROTATION MATRICE AROUND AXIS APPLIED TO VECTOR */
	/* axis = transf_coord(vector.y, -vector.x, vector.z);
	vector = transf_coord((pow(axis.x, 2) * (1 - cos(angle_ver)) + cos(angle_ver)) * vector.x + \
	(axis.x * axis.y * (1 - cos(angle_ver)) - axis.z * sin(angle_ver)) * vector.y + \
	(axis.x * axis.z * (1 - cos(angle_ver)) + axis.y * sin(angle_ver)) * vector.z, \
	(axis.x * axis.y * (1 - cos(angle_ver)) + axis.z * sin(angle_ver)) * vector.x + \
	(pow(axis.y, 2) * (1 - cos(angle_ver)) + cos(angle_ver)) * vector.y + \
	(axis.y * axis.z * (1 - cos(angle_ver)) - axis.x * sin(angle_ver)) * vector.z, \
	(axis.x * axis.z * (1 - cos(angle_ver)) - axis.y * sin(angle_ver)) * vector.x + \
	(axis.y * axis.z * (1 - cos(angle_ver)) + axis.x * sin(angle_ver)) * vector.y + \
	(pow(axis.z, 2) * (1 - cos(angle_ver)) + cos(angle_ver)) * vector.z); */
		
	/* printf("i:%d j:%d (%f°, %f°)", i, j, angle_hor * 180 / M_PI, angle_ver * 180 / M_PI);
	print_coord(&vector);
	printf("\n"); */
	(void)axis;
	return (vector);
}

/* get case integral coordinates of a point according to a vector */
t_coord	get_case(t_coord vector, t_coord point, int p)
{
	t_coord	_case;

	if (p == NEXT && vector.y > EPSILON)
		_case.y = floor(point.y) + 1;
	else if (p == NEXT)
		_case.y = ceil(point.y) - 1;
	if (p == NEXT && vector.x > EPSILON)
		_case.x = floor(point.x) + 1;
	else if (p == NEXT)
		_case.x = ceil(point.x) - 1;
	if (p == NEXT && vector.z > EPSILON)
		_case.z = floor(point.z) + 1;
	else if (p == NEXT)
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
void	raycasting_put(t_coord pint, t_cubdata *cub, t_point pscr, t_coord vector)
{
	t_img_data	*canvas;
	t_point		pimg;
	t_img_data	*img;
	char		orientation;
	t_coord		_case;

	canvas = get_canvas(&cub->data, MAIN);
	_case = get_case(vector, pint, CURRENT);
	if (pint.z <= EPSILON)
		return (my_mlx_pixel_put(canvas, pscr.x, pscr.y, cub->f_color));
	if (pint.z >= 1 - EPSILON)
		return (my_mlx_pixel_put(canvas, pscr.x, pscr.y, cub->c_color));
	if (fabs(pint.y - _case.y) < EPSILON)
		orientation = 'S';
	else if (fabs(pint.y - _case.y - 1) < EPSILON)
		orientation = 'N';
	else if (fabs(pint.x - _case.x) < EPSILON)
		orientation = 'E';
	else
		orientation = 'W';
	img = new_image(&cub->data, orientation, NULL, NULL);
	pimg.y = (pint.z - floor(pint.z)) * img->height;
	if (pint.x - floor(pint.x) < EPSILON)
		pimg.x = (pint.y - floor(pint.y)) * img->width;
	else
		pimg.x = (pint.x - floor(pint.x)) * img->width;
	my_mlx_pixel_put(canvas, pscr.x, pscr.y, ((int *)img->addr)[pimg.y * img->height + pimg.x]);
	/* DEBUGGING */
/*	printf("i:%d j:%d ", pscr.y, pscr.x);
	print_coord(&pint);
	print_coord(&vector);
	printf("\n"); */
}

/* returns coordinates of the intersection between vector and a wall */
/* recursive version */
t_coord	intersection(t_coord start, t_coord vector, t_map *map)
{
	t_coord		_case;
	double		min;
	static int	count = 0;

	_case = get_case(vector, start, CURRENT);
	if (count > 1000 || start.z <= EPSILON || start.z >= 1 - EPSILON || \
		map->tab[(int)(_case.y)][(int)(_case.x)] == 1)
		return (ft_bzero(&count, sizeof(int)), start);
	_case = get_case(vector, start, NEXT);
	min = 0;
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
	start = transf_coord(start.x + min * vector.x, start.y + min * vector.y, \
						start.z + min * vector.z);
	return (count++, intersection(start, vector, map));
}
/* iterative version*/
/* t_coord	intersection(t_coord start, t_coord vector, t_map *map)
{
	t_coord		_case;
	t_coord		point;
	double		min;
	int			count;

	count = 0;
	point = start;
	_case = get_case(vector, point, CURRENT);
	while (count++ < 1000 && point.z > EPSILON && point.z < 1 - EPSILON && \
		map->tab[(int)(_case.y)][(int)(_case.x)] != 1)
	{
		min = 0;
		_case = get_case(vector, point, NEXT);
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
		point = transf_coord(start.x + min * vector.x, \
				start.y + min * vector.y, start.z + min * vector.z);
		_case = get_case(vector, point, CURRENT);
	}
	return (point);
} */

/* go through every pixel of the screen and apply raycasting method */
void	raycasting(t_cubdata *cub)
{
	t_data		*data;
	t_img_data	*canvas;
	int			i;
	int			j;
	t_coord		vector;
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;

	clock_gettime(CLOCK_REALTIME, &start);
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
	clock_gettime(CLOCK_REALTIME, &end);
	//printf("raycasting : %f seconds\n", time_diff(&start, &end));
}
