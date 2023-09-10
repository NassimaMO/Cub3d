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

/* expecting : changes->p1=direction */
void	rotate(t_param *p, t_changes *changes, int i, int j)
{
	if (changes->p1 == ANTICLOCKW)
	{
		((int *)p->new_img->addr)[i * p->new_img->width + j] = \
		((int *)p->img->addr)[j * p->img->width + (p->img->width - i - 1)];
	}
	if (changes->p1 == CLOCKW)
	{
		((int *)p->new_img->addr)[i * p->new_img->width + j] = \
		((int *)p->img->addr)[(p->img->height - j - 1) * p->img->width + i];
	}
}

/* expecting : changes->p1=direction */
void	invert(t_param *p, t_changes *changes, int i, int j)
{
	if (changes->p1 == RIGHT || changes->p1 == LEFT)
	{
		((int *)p->new_img->addr)[i * p->img->width + j] = \
		((int *)p->img->addr)[i * p->img->width + (p->img->width - j - 1)];
	}
	if (changes->p1 == UP || changes->p1 == DOWN)
	{
		((int *)p->new_img->addr)[i * p->img->width + j] = \
		((int *)p->img->addr)[(p->img->height - i - 1) * p->img->width + j];
	}
}

/* expecting : changes->p1=width_start, changes->p2=height_start
	changes->p3=width, changes->p4=height */
void	cut(t_param *p, t_changes *changes, int i, int j)
{
	((int *)p->new_img->addr)[i * changes->p3 + j] = ((int *)p->img->addr) \
	[(i + changes->p2) * p->img->width + (j + changes->p1)];
}

/* expecting : changes->p1=color */
void	recolor(t_param *p, t_changes *changes, int i, int j)
{
	int	pix;

	pix = ((int *)p->img->addr)[i * p->img->width + j];
	if (pix >= 0)
		((int *)p->new_img->addr)[i * p->img->width + j] = changes->p1;
	else
		((int *)p->new_img->addr)[i * p->img->width + j] = pix;
}
