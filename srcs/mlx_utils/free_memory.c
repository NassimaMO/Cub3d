/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:14:33 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/31 11:14:35 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_img(void *p)
{
	t_img_data	*img;

	img = p;
	if (img->ptr)
	{
		if (((t_img *)(img->ptr))->image)
			XDestroyImage(((t_img *)(img->ptr))->image);
		free(img->ptr);
	}
	if (img->changes)
		ft_lstclear(&(img->changes), &free);
}

void	free_img_list(t_list **list)
{
	if (*list)
	{
		ft_lstiter(*list, &free_img);
		ft_lstclear(list, &free);
	}
}

void	free_data(t_data *data)
{
	free_img_list(&(data->imgs));
	free_img_list(&(data->canvases));
	if (!data->mlx_ptr)
		return ;
	if (data->win.ptr)
		mlx_destroy_window(data->mlx_ptr, data->win.ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
