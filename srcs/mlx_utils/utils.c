/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:58:19 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:58:20 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_init(int *n1, int *n2, int *n3, int *n4)
{
	if (n1 == NULL)
		return ;
	*n1 = 0;
	if (n2 == NULL)
		return ;
	*n2 = 0;
	if (n3 == NULL)
		return ;
	*n3 = 0;
	if (n4 == NULL)
		return ;
	*n4 = 0;
}

t_point	transf_point(int x, int y)
{
	t_point	a;

	a.x = x;
	a.y = y;
	return (a);
}

void	center_coord(int *width, int *height, t_img_data *canvas)
{
	if (*width > canvas->width)
		*width = canvas->width;
	if (*height > canvas->height)
		*height = canvas->height;
	*width = (canvas->width - *width) / 2;
	*height = (canvas->height - *height) / 2;
}
