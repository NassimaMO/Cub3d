/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:12:29 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/31 11:12:30 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_img(t_data *data, t_img_data *img, int id, char *(fpath)(int ))
{
	char	*path;

	ft_bzero(img, sizeof(t_img_data));
	path = fpath(id);
	img->id = id;
	if (!path)
		return ;
	img->ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, \
	&(img->width), &(img->height));
	if (!img->ptr)
		return (free(path));
	img->addr = mlx_get_data_addr(img->ptr, &(img->bpp), \
	&(img->line_length), &(img->endian));
	img->changes = NULL;
	free(path);
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
	return (1);
}

t_changes	transf_c(void (f)(t_param *, t_changes *, int, int), ...)
{
	va_list		args;
	t_changes	change;

	ft_bzero(&change, sizeof(t_changes));
	change.ptr = f;
	if (!f)
		return (change);
	va_start(args, f);
	change.p1 = va_arg(args, int);
	if (f == &cut || f == &alpha || f == &resize)
	{
		change.p2 = va_arg(args, int);
		change.p3 = va_arg(args, int);
		if (f != &resize)
			change.p4 = va_arg(args, int);
	}
	va_end(args);
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
