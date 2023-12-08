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

t_coord	get_vector(t_img_data *canvas, int j, int i, t_cubdata *cub)
{
	/* t_coord	vector_hor;
	t_coord	vector_ver; */
	t_coord	vector;
	t_coord	cam;
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;
	clock_gettime(CLOCK_REALTIME, &start);

	cam.x = (j - canvas->width / 2.0);
	cam.y = (canvas->height / 2.0 - i);
	vector.x = cub->player.pos.x + cub->cam.dir.x + cub->cam.hor.x \
	* cam.x + cub->cam.ver.x * cam.y;
	vector.y = cub->player.pos.y + cub->cam.dir.y + cub->cam.hor.y \
	* cam.x + cub->cam.ver.y * cam.y;
	vector.z = cub->player.pos.z + cub->cam.dir.z + cub->cam.hor.z \
	* cam.x + cub->cam.ver.z * cam.y;
	clock_gettime(CLOCK_REALTIME, &end);
	average_time("get_vector", time_diff(&start, &end));
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
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;
	clock_gettime(CLOCK_REALTIME, &start);

	canvas = get_canvas(&cub->data, MAIN);
	if (pint.z <= EPSILON)
		return (my_mlx_pixel_put(canvas, pscr.x, pscr.y, cub->f_color));
	if (pint.z >= 1 - EPSILON)
		return (my_mlx_pixel_put(canvas, pscr.x, pscr.y, cub->c_color));
	_case = get_case(vector, pint, CURRENT);
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
	clock_gettime(CLOCK_REALTIME, &end);
	average_time("raycasting_put", time_diff(&start, &end));
}

/* returns coordinates of the intersection between vector and a wall */
/* recursive version */
t_coord	intersection(t_coord point, t_coord vector, t_map *map)
{
	t_coord		_case;
	double		min;
	static int	count = 0;
	//DEBUGGING
	static struct timespec	start = {0};
	struct timespec			end;
	if (!start.tv_sec)
		clock_gettime(CLOCK_REALTIME, &start);

	_case = get_case(vector, point, CURRENT);
	if (count > 1000 || point.z <= EPSILON || point.z >= 1 - EPSILON || \
		map->tab[(int)(_case.y)][(int)(_case.x)] == 1)
	{
		clock_gettime(CLOCK_REALTIME, &end);
		average_time("intersection", time_diff(&start, &end));
		ft_bzero(&start, sizeof(struct timespec));
		return (ft_bzero(&count, sizeof(int)), point);
	}
	_case = get_case(vector, point, NEXT);
	min = 0;
	if (fabs(vector.x) >= EPSILON)
		min = fabs((_case.x - point.x) / vector.x);
	else if (fabs(vector.y) >= EPSILON)
		min = fabs((_case.y - point.y) / vector.y);
	else if (fabs(vector.z) >= EPSILON)
		min = fabs((_case.z - point.z) / vector.z);
	if (fabs(vector.x) >= EPSILON)
		min = fmin(min, fabs((_case.x - point.x) / vector.x));
	if (fabs(vector.y) >= EPSILON)
		min = fmin(min, fabs((_case.y - point.y) / vector.y));
	if (fabs(vector.z) >= EPSILON)
		min = fmin(min, fabs((_case.z - point.z) / vector.z));
	point = transf_coord(point.x + min * vector.x, point.y + min * vector.y, \
						point.z + min * vector.z);
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
			raycasting_put(intersection(cub->player.pos, \
			vector, &cub->map), cub, transf_point(j, i), vector);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win.ptr, canvas->ptr, 0, 0);
	clock_gettime(CLOCK_REALTIME, &end);
	average_time("raycasting", time_diff(&start, &end));
}
