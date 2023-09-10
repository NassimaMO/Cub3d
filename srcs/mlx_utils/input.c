/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:06:47 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/31 11:06:50 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	ft_exit(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	no_input(t_data *data)
{
	(void)data;
	return (0);
}

int	input_escape(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		ft_exit(data);
		return (1);
	}
	return (0);
}
