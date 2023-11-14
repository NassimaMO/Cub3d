/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:15:25 by nghulam-          #+#    #+#             */
/*   Updated: 2023/10/28 15:57:56 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_cubdata	cub;
	t_data		*data;

	if (argc != 2)
		return (print_errors(ERR_ARGS));
	ft_bzero(&cub, sizeof(t_cubdata));
	if (parse_info(argv[1], &cub))
		return (print_errors(ERR_PARSING));
	data = (init_data(&cub.data), fill_data(argv[1], &cub), &cub.data);
	if (parse_map_walls(&cub.map))
		return (free_cubdata(&cub), print_errors(ERR_PARSING));
	cub.settings.fov = FOV;
	cub.settings.sens = 1;
	raycasting(&cub);
	mlx_loop_hook(data->mlx_ptr, &no_input, data);
	mlx_hook(data->win.ptr, DestroyNotify, StructureNotifyMask, &ft_exit, data);
	mlx_hook(data->win.ptr, KeyPress, KeyPressMask, &input, &cub);
	mlx_loop(data->mlx_ptr);
	return (free_cubdata(&cub), 0);
}
