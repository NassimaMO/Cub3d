/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:50:46 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:50:47 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	linear_scale(t_param *p, int i, int j)
{
	int	y;
	int	x;
	int	width;
	int	height;

	width = p->new_img->width;
	height = p->new_img->height;
	y = i * ((float)p->img->height / height);
	x = j * ((float)p->img->width / width);
	((unsigned int *)(p->new_img->addr))[i * width + j] = \
	((unsigned int *)p->img->addr)[y * p->img->width + x];
}

/* expecting (int, int, int, int h_end, t_img_data *img) */
static int	loop_average(int w_start, int w_end, int h_start, ...)
{
	int			k;
	int			l;
	va_list		args;
	int			h_end;
	t_img_data	*img;

	va_start(args, h_start);
	h_end = va_arg(args, int);
	img = va_arg(args, t_img_data *);
	va_end(args);
	average_color(START, 0);
	k = w_start;
	while (k < w_end)
	{
		l = h_start;
		while (l < h_end)
		{
			average_color(MID, ((unsigned int *)img->addr)[l * img->width + k]);
			l++;
		}
		k++;
	}
	return (average_color(END, 0));
}

static void	box_downscale(t_param *p, int i, int j)
{
	int	y;
	int	x;
	int	x_end;
	int	y_end;
	int	pixel;

	x_end = (double)p->img->width / p->new_img->width;
	x_end += (x_end != p->img->width / p->new_img->width);
	y_end = (double)p->img->height / p->new_img->height;
	y_end += (y_end != p->img->height / p->new_img->height);
	y = i * ((double)p->img->height / p->new_img->height);
	x = j * ((double)p->img->width / p->new_img->width);
	y_end = ft_min(2, y + y_end, p->img->height - 1);
	x_end = ft_min(2, x + x_end, p->img->width - 1);
	pixel = loop_average(x, x_end, y, y_end, p->img);
	((int *)(p->new_img->addr))[i * p->new_img->width + j] = pixel;
}

/* expecting : changes->p1=resize_parameter */
void	resize(t_param *p, t_changes *changes, int i, int j)
{
	static t_list	*old_changes;

	if (i == 0 && j == 0)
	{
		if (changes->p1 == ORIGINAL)
		{
			if (changes->p2 == ft_min(2, changes->p2, \
			p->img->width * changes->p3 / p->img->height))
				changes->p3 = p->img->height * changes->p2 / p->img->width;
			else
				changes->p2 = p->img->width * changes->p3 / p->img->height;
		}
		old_changes = p->new_img->changes;
		init_canvas(p->data, p->new_img, changes->p2, changes->p3);
		p->new_img->changes = old_changes;
	}
	if (i > changes->p3 || j > changes->p2)
		return ;
	if (changes->p2 <= p->img->width && changes->p3 <= p->img->height)
		return (box_downscale(p, i, j));
	return (linear_scale(p, i, j));
}
