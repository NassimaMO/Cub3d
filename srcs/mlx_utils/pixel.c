/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:39:55 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:40:00 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	background_pix(t_img_data *canvas, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->width)
	{
		j = 0;
		while (j < canvas->height)
		{
			my_mlx_pixel_put(canvas, i, j, color);
			j++;
		}
		i++;
	}
}

void	background_gradient(t_img_data *canvas, int start, int end, int p)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	if (p != HOR && p != VER)
		p = VER;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			if (p == HOR)
				color = add_color(start, end, 100 * (float)j / canvas->width);
			if (p == VER)
				color = add_color(start, end, 100 * (float)i / canvas->height);
			my_mlx_pixel_put(canvas, j, i, color);
			j++;
		}
		i++;
	}
}

void	image_put(t_img_data *canvas, t_img_data *img, t_point a, int p)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;

	if (!img)
		return ;
	dst = canvas->addr + (a.y * canvas->line_length + a.x * (canvas->bpp / 8));
	src = img->addr;
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			if (p == ALL || *((int *)src) >= 0)
				*((int *)dst) = *((int *)src);
			src += (canvas->bpp / 8);
			dst += (canvas->bpp / 8);
			j++;
		}
		i++;
		dst += canvas->line_length - img->line_length;
	}
}

void	put_canvas(t_data *data, int id_src, int id_dest)
{
	t_img_data	*canvas_src;
	t_img_data	*canvas_dest;
	t_point		a;

	canvas_src = get_canvas(data, id_src);
	canvas_dest = get_canvas(data, id_dest);
	a.x = canvas_src->width;
	a.y = canvas_src->height;
	center_coord(&(a.x), &(a.y), canvas_dest);
	image_put(canvas_dest, canvas_src, a, TRANSP);
}
