/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:12:29 by nghulam-          #+#    #+#             */
/*   Updated: 2023/10/24 18:58:02 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_img(t_data *data, t_img_data *img, int id, char *path)
{
	ft_bzero(img, sizeof(t_img_data));
	img->id = id;
	if (!path)
		return ;
	img->ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, \
	&(img->width), &(img->height));
	if (!img->ptr)
		return ;
	img->addr = mlx_get_data_addr(img->ptr, &(img->bpp), \
	&(img->line_length), &(img->endian));
	img->changes = NULL;
	img->mlx_ptr = data->mlx_ptr;
}

int	init_canvas(t_data *data, t_img_data *canvas, int width, int height)
{
	canvas->ptr = mlx_new_image(data->mlx_ptr, width, \
	height);
	if (!canvas->ptr)
		return (0);
	canvas->addr = mlx_get_data_addr(canvas->ptr, \
	&(canvas->bpp), &(canvas->line_length), &(canvas->endian));
	canvas->width = width;
	canvas->height = height;
	ft_memset(canvas->addr, -1, canvas->line_length * canvas->height);
	canvas->changes = NULL;
	canvas->mlx_ptr = data->mlx_ptr;
	return (1);
}

t_changes	transf_c(void (f)(t_param, t_changes *, int, int), \
										const void *p1, int p2, int p3)
{
	t_changes	change;

	change.f = (ft_bzero(&change, sizeof(t_changes)), f);
	if (f == &resize)
	{
		change.new_width = *((int *)p1);
		change.new_height = p2;
		change.scale = p3;
	}
	if (f == &recolor)
		change.color = p3;
	if (f == &alpha)
		change.canvas_id = p2;
	if (f == &alpha)
		change.alpha_lvl = p3;
	if (f == &rotate || f == &invert)
		change.direction = p3;
	if (f == &cut)
	{
		change.start = transf_point(((t_point *)p1)->x, ((t_point *)p1)->y);
		change.new_width = p2;
		change.new_height = p3;
	}
	return (change);
}

t_font	transf_font(int x, int y, int size, int color)
{
	t_font	param;

	param.x = x;
	param.y = y;
	param.size = size;
	param.color = color;
	return (param);
}
