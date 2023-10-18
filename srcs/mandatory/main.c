/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:15:25 by nghulam-          #+#    #+#             */
/*   Updated: 2022/09/23 12:15:37 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cubdata	cub;
	t_data		*data;
	t_img_data	*canvas;

	if (argc != 2)
		return (print_errors(ERR_ARGS));
	if (parse_info(argv[1]))
		return (print_errors(ERR_PARSING));
	data = &cub.data;
	init_data(&data);
	canvas = get_canvas(&data, MAIN);
	mlx_put_image_to_window(data.mlx_ptr, data.win.ptr, canvas->ptr, 0, 0);
	mlx_loop_hook(data.mlx_ptr, &no_input, &data);
	mlx_hook(data.win.ptr, DestroyNotify, StructureNotifyMask, &ft_exit, &data);
	mlx_hook(data.win.ptr, KeyPress, KeyPressMask, &input, &data);
	mlx_loop(data.mlx_ptr);
	free_cubdata(&cub);
	return (0);
}
