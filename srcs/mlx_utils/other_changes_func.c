/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_changes_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:55:58 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:55:59 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

/* using : changes->direction */
void	rotate(t_param p, t_changes *changes, int i, int j)
{
	if (changes->direction == ANTICLOCKW)
	{
		((int *)p.new_img->addr)[i * p.new_img->width + j] = \
		((int *)p.img->addr)[j * p.img->width + (p.img->width - i - 1)];
	}
	if (changes->direction == CLOCKW)
	{
		((int *)p.new_img->addr)[i * p.new_img->width + j] = \
		((int *)p.img->addr)[(p.img->height - j - 1) * p.img->width + i];
	}
}

/* using : changes->direction */
void	invert(t_param p, t_changes *changes, int i, int j)
{
	if (changes->direction == VER)
	{
		((int *)p.new_img->addr)[i * p.img->width + j] = \
		((int *)p.img->addr)[i * p.img->width + (p.img->width - j - 1)];
	}
	if (changes->direction == HOR)
	{
		((int *)p.new_img->addr)[i * p.img->width + j] = \
		((int *)p.img->addr)[(p.img->height - i - 1) * p.img->width + j];
	}
}

/* using : changes->start, changes->new_width, changes->new_height */
void	cut(t_param p, t_changes *changes, int i, int j)
{
	((int *)p.new_img->addr)[i * p.new_img->width + j] = \
	((int *)p.img->addr)[(i + changes->start.y) * p.img->width \
											+ (j + changes->start.x)];
}

/* using : changes->color */
void	recolor(t_param p, t_changes *changes, int i, int j)
{
	int	pix;

	pix = ((int *)p.img->addr)[i * p.img->width + j];
	if (pix >= 0)
		((int *)p.new_img->addr)[i * p.img->width + j] = changes->color;
	else
		((int *)p.new_img->addr)[i * p.img->width + j] = pix;
}
