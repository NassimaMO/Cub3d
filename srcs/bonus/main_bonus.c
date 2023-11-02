/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:08:13 by nghulam-          #+#    #+#             */
/*   Updated: 2023/01/04 18:08:14 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	t_img_data	*canvas;

	init_data(&data);
	canvas = get_canvas(&data, MAIN);
	mlx_put_image_to_window(data.mlx_ptr, data.win.ptr, canvas->ptr, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &no_input, &data);
	mlx_hook(data.win.ptr, DestroyNotify, StructureNotifyMask, &ft_exit, &data);
	mlx_hook(data.win.ptr, KeyPress, KeyPressMask, &input, &data);
	mlx_loop(data.mlx_ptr);
	free_data(&data);
	(void)argc;
	(void)argv;
	return (0);
}
