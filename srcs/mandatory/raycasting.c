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
	t_coord	vector;
	t_coord	cam;

	cam.x = (j - canvas->width / 2.0);
	cam.y = (canvas->height / 2.0 - i);
	vector.x = cub->player.pos.x + cub->cam.dir.x + cub->cam.hor.x \
	* cam.x + cub->cam.ver.x * cam.y;
	vector.y = cub->player.pos.y + cub->cam.dir.y + cub->cam.hor.y \
	* cam.x + cub->cam.ver.y * cam.y;
	vector.z = cub->player.pos.z + cub->cam.dir.z + cub->cam.hor.z \
	* cam.x + cub->cam.ver.z * cam.y;
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

/* calculate wall c and put the right pixel color 
according to intersection point*/
void	raycasting_put(t_coord pint, t_cubdata *cub, t_point pscr, \
															t_coord vector)
{
	t_img_data	*scr;
	t_point		pimg;
	t_img_data	*img;
	char		c;

	scr = get_canvas(&cub->data, MAIN);
	if (!scr)
		return ((void)ft_exit(&cub->data));
	if (pint.z <= EPSILON)
		return (pix(scr, pscr.x, pscr.y, cub->f_color));
	if (pint.z >= 1 - EPSILON)
		return (pix(scr, pscr.x, pscr.y, cub->c_color));
	c = get_orientation(pint, vector);
	img = new_image(&cub->data, c, NULL, NULL);
	if (!img)
		return (pix(scr, pscr.x, pscr.y, \
			(((c & 4) << 16) * 220 + ((c & 2) << 8) * 220 + (c & 1) * 220)));
	pimg.y = (pint.z - floor(pint.z)) * img->height;
	pimg.x = (pint.x - floor(pint.x)) * img->width;
	if (pint.x - floor(pint.x) < EPSILON)
		pimg.x = (pint.y - floor(pint.y)) * img->width;
	pix(scr, pscr.x, pscr.y, ((int *)img->addr)[pimg.y * img->height + pimg.x]);
}

/* returns coordinates of the intersection between vector and a wall */
/* recursive version */
t_coord	intersection(t_coord point, t_coord vector, t_map *map)
{
	t_coord		_case;
	double		min;
	static int	count = 0;

	_case = get_case(vector, point, CURRENT);
	if (count > 1000 || point.z <= EPSILON || point.z >= 1 - EPSILON || \
		_case.y >= map->height || _case.x >= map->width || _case.y < 0 || \
			_case.x < 0 || map->tab[(int)_case.y][(int)_case.x] == WALL)
		return (ft_bzero(&count, sizeof(int)), point);
	_case = (ft_bzero(&min, sizeof(int)), get_case(vector, point, NEXT));
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

	i = 0;
	data = &cub->data;
	canvas = get_canvas(data, MAIN);
	if (!canvas)
		return ((void)ft_exit(&cub->data));
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
}

/* void	raycasting(t_cubdata *cub)
{
	t_img_data	*canvas;
	int			i;
	int			j;
	t_coord		v;
	t_coord		u;
	t_coord		p;
	t_coord		pi;
	double		d;

	j = 0;
	canvas = get_canvas(&cub->data, MAIN);
	while (j < canvas->width)
	{
		v = get_vector(canvas, j, 0, cub);
		v.z = 0;
		p = intersection(cub->player.pos, v, &cub->map);
		d = sqrt(pow(p.x -cub->player.pos.x, 2) + \
						pow(p.y -cub->player.pos.y, 2));
		v = normalize(v, 1);
		i = 0;
		while (i < canvas->height)
		{
			u = normalize(get_vector(canvas, j, i, cub), 1);
			pi = p;
			if (u.z > 0)
				pi.z += tan(acos(u.x * v.x + u.y * v.y + u.z * v.z)) * d;
			else
				pi.z -= tan(acos(u.x * v.x + u.y * v.y + u.z * v.z)) * d;
			raycasting_put(pi, cub, transf_point(j, i), u);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(cub->data.mlx_ptr, cub->data.win.ptr, \ 
												canvas->ptr, 0, 0);
} */
