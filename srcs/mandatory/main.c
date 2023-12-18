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

static void	settings(t_cubdata *cub)
{
	ft_bzero(cub, sizeof(t_cubdata));
	cub->settings.fov = FOV;
	cub->settings.sens = 1;
}

int	main(int argc, char *argv[])
{
	t_cubdata	cub;
	t_data		*data;

	if (argc != 2 || check_ext(argv[1]))
		return (print_errors(ERR_ARGS));
	settings(&cub);
	data = &cub.data;
	if (print_errors(parse_info(argv[1], &cub)))
		return (EXIT_FAILURE);
	if (print_errors(init_data(data)))
		return (EXIT_FAILURE);
	if (print_errors(fill_data(open(argv[1], O_RDONLY), &cub)))
		return (free_cubdata(&cub), EXIT_FAILURE);
	if (print_errors(parse_map_walls(&cub.map)))
		return (free_cubdata(&cub), EXIT_FAILURE);
	raycasting(&cub);
	mlx_do_key_autorepeaton(data->mlx_ptr);
	mlx_loop_hook(data->mlx_ptr, &no_input, data);
	mlx_hook(data->win.ptr, KeyPress, KeyPressMask, &input, &cub);
	mlx_hook(data->win.ptr, DestroyNotify, StructureNotifyMask, &ft_exit, data);
	mlx_loop(data->mlx_ptr);
	return (free_cubdata(&cub), 0);
}
