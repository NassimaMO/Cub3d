/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:54:30 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:54:31 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	add_color(unsigned int dest, unsigned int src, int alpha_lvl)
{
	unsigned int	rgb_dest;
	unsigned int	rgb_src;
	unsigned int	n;

	n = 0;
	rgb_dest = dest >> 8 * 3;
	rgb_src = src >> 8 * 3;
	n = (rgb_dest * (100 - alpha_lvl) + (rgb_src * alpha_lvl)) / 100 << 8 * 3;
	rgb_dest = (dest << 8 * 1) >> 8 * 3;
	rgb_src = (src << 8 * 1) >> 8 * 3;
	n = (rgb_dest * (100 - alpha_lvl) + (rgb_src * alpha_lvl)) / 100 << 8 * 2;
	rgb_dest = (dest << 8 * 2) >> 8 * 3;
	rgb_src = (src << 8 * 2) >> 8 * 3;
	n += (rgb_dest * (100 - alpha_lvl) + (rgb_src * alpha_lvl)) / 100 << 8 * 1;
	rgb_dest = (dest << 8 * 3) >> 8 * 3;
	rgb_src = (src << 8 * 3) >> 8 * 3;
	n += (rgb_dest * (100 - alpha_lvl) + (rgb_src * alpha_lvl)) / 100 ;
	return (n);
}

int	average_color(int status, unsigned int pixel, int *sum, int *n)
{
	if (status == START)
	{
		sum[0] = 0;
		sum[1] = 0;
		sum[2] = 0;
		sum[3] = 0;
		*n = 0;
		return (0);
	}
	if (status == END)
	{
		if (*n != 0)
			return (((sum[0] / *n) << 8 * 3) + ((sum[1] / *n) << 8 * 2) + \
			((sum[2] / *n) << 8 * 1) + sum[3] / *n);
		return (0);
	}
	sum[0] += pixel >> 8 * 3;
	sum[1] += (pixel << 8 * 1) >> 8 * 3;
	sum[2] += (pixel << 8 * 2) >> 8 * 3;
	sum[3] += (pixel << 8 * 3) >> 8 * 3;
	(*n)++;
	return (0);
}

/* using : changes->alpha_lvl, changes->canvas_id */
void	alpha(t_param p, t_changes *changes, int i, int j)
{
	int	img_pix;
	int	bg_pix;

	img_pix = ((int *)p.img->addr)[i * p.img->width + j];
	if (img_pix >= 0)
	{
		bg_pix = ((int *)p.canvas->addr)[(changes->new_height + i) * \
							p.canvas->width + (changes->new_width + j)];
		((int *)p.new_img->addr)[i * p.img->width + j] = \
							add_color(img_pix, bg_pix, changes->alpha_lvl);
	}
	else
		((int *)p.new_img->addr)[i * p.img->width + j] = img_pix;
}
