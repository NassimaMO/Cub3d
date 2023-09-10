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

int	average_color(int status, unsigned int pixel)
{
	static int	a_sum = 0;
	static int	r_sum = 0;
	static int	g_sum = 0;
	static int	b_sum = 0;
	static int	n = 0;

	if (status == END)
	{
		if (n != 0)
			n = ((a_sum / n) << 8 * 3) + ((r_sum / n) << 8 * 2) + \
			((g_sum / n) << 8 * 1) + b_sum / n;
		return (n);
	}
	if (status == START)
	{
		return (ft_init(5, &a_sum, &r_sum, &g_sum, &b_sum, &n), n);
	}
	a_sum += pixel >> 8 * 3;
	r_sum += (pixel << 8 * 1) >> 8 * 3;
	g_sum += (pixel << 8 * 2) >> 8 * 3;
	b_sum += (pixel << 8 * 3) >> 8 * 3;
	return (++n);
}

int	get_pix(t_img_data *canvas, ...)
{
	va_list			args;
	int				x;
	int				y;
	int				i;
	int				j;

	va_start(args, canvas);
	x = va_arg(args, int);
	y = va_arg(args, int);
	i = va_arg(args, int);
	j = va_arg(args, int);
	va_end(args);
	j = ((int *)canvas->addr)[(y + i) * canvas->width + x + j];
	return (j);
}

/* expecting changes->p1=canvas_id, ->p2=x, ->p3=y, ->p4=alpha_level) */
void	alpha(t_param *p, t_changes *changes, int i, int j)
{
	t_img_data	*canvas;
	int			pix;

	canvas = get_canvas(p->data, changes->p1);
	pix = ((int *)p->img->addr)[i * p->img->width + j];
	if (pix >= 0)
		((int *)p->new_img->addr)[i * p->img->width + j] = add_color(pix, \
		get_pix(canvas, changes->p2, changes->p3, i, j), changes->p4);
	else
		((int *)p->new_img->addr)[i * p->img->width + j] = pix;
}
