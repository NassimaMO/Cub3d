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

static int	loop_average(t_point start, t_point end, t_img_data *img)
{
	int			sum[4];
	int			n;

	average_color(START, 0, sum, &n);
	while (start.x < end.x)
	{
		while (start.y < end.y)
		{
			average_color(MID, ((unsigned int *)img->addr)[start.y * \
										img->width + start.x], sum, &n);
			start.y++;
		}
		start.x++;
	}
	return (average_color(END, 0, sum, &n));
}

static void	box_downscale(t_param *p, int i, int j)
{
	t_point	start;
	t_point	end;
	int		pixel;

	end.x = p->img->width / p->new_img->width;
	end.y = p->img->height / p->new_img->height;
	start.y = i * ((double)p->img->height / p->new_img->height);
	start.x = j * ((double)p->img->width / p->new_img->width);
	end.y = fmin(start.y + end.y, p->img->height - 1);
	end.x = fmin(start.x + end.x, p->img->width - 1);
	pixel = loop_average(start, end, p->img);
	((int *)(p->new_img->addr))[i * p->new_img->width + j] = pixel;
}

/* using : changes->scale, changes->new_width, changes->new_height */
void	resize(t_param p, t_changes *changes, int i, int j)
{
	if (i > changes->new_height || j > changes->new_width)
		return ;
	if (changes->new_width <= p.img->width && \
		changes->new_height <= p.img->height)
		return (box_downscale(&p, i, j));
	return (linear_scale(&p, i, j));
}
