/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:12:22 by nghulam-          #+#    #+#             */
/*   Updated: 2023/10/24 18:03:51 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_img_data	*alloc_img(t_data *data, int id, char *path)
{
	t_img_data	*img;
	t_list		*ptr;

	img = malloc(sizeof(t_img_data));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_img_data));
	ptr = ft_lstnew(img);
	if (!ptr)
		return (free(img), NULL);
	ft_lstadd_back(&(data->imgs), ptr);
	init_img(data, img, id, path);
	if (!img->ptr)
	{
		ft_lstsuppr(&(data->imgs), ft_lstlast(data->imgs), &free);
		return (NULL);
	}
	return (img);
}

int	alloc_canvas(t_data *data, int width, int height, int id)
{
	t_img_data	*canvas;
	t_list		*ptr;

	if (get_canvas(data, id))
		return (2);
	canvas = malloc(sizeof(t_img_data));
	if (!canvas)
		return (1);
	init_canvas(data, canvas, width, height);
	if (!canvas->ptr)
		return (free(canvas), 1);
	canvas->id = id;
	ptr = ft_lstnew(canvas);
	if (!ptr)
		return (free_img(canvas), free(canvas), 1);
	ft_lstadd_back(&(data->canvases), ptr);
	return (0);
}

void	*dup_change(void *change)
{
	t_changes	*new;
	t_changes	*ref;

	ref = change;
	new = malloc(sizeof(t_changes));
	if (!new)
		return (NULL);
	*new = *ref;
	return (new);
}

int	alloc_c(t_list **list, t_changes changes)
{
	t_changes	*new;
	t_list		*ptr;

	new = dup_change(&changes);
	if (!new)
		return (1);
	ptr = ft_lstnew(new);
	if (!ptr)
		return (free(new), 1);
	return (ft_lstadd_back(list, ptr), 0);
}
