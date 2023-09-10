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

int	ft_max(int nb, ...)
{
	int		i;
	va_list	args;
	int		n;
	int		max;

	i = 0;
	va_start(args, nb);
	while (i < nb)
	{
		n = va_arg(args, int);
		if (i == 0)
			max = n;
		else if (n > max)
			max = n;
		i++;
	}
	va_end(args);
	return (max);
}

int	ft_min(int nb, ...)
{
	int		i;
	va_list	args;
	int		n;
	int		min;

	i = 0;
	va_start(args, nb);
	while (i < nb)
	{
		n = va_arg(args, int);
		if (i == 0)
			min = n;
		else if (n < min)
			min = n;
		i++;
	}
	va_end(args);
	return (min);
}

void	ft_init(int nb, ...)
{
	int		i;
	va_list	args;
	int		*n;

	i = 0;
	va_start(args, nb);
	while (i < nb)
	{
		n = va_arg(args, int *);
		*n = 0;
		i++;
	}
	va_end(args);
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
