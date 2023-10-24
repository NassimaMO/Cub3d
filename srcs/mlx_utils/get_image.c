/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:48:09 by nghulam-          #+#    #+#             */
/*   Updated: 2023/10/24 18:05:20 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_img_data	*get_canvas(t_data *data, int id)
{
	t_list	*list;

	list = data->canvases;
	while (list)
	{
		if (((t_img_data *)list->content)->id == id)
			return (list->content);
		list = list->next;
	}
	return (NULL);
}

t_img_data	*get_image(t_data *data, int id, t_list *changes)
{
	t_list		*ptr;
	t_img_data	*img;
	int			count;

	ptr = data->imgs;
	while (ptr)
	{
		img = ptr->content;
		if (img->id == id)
		{
			count = count_common(changes, img->changes, &is_equal_changes);
			if (ft_lstsize(img->changes) == count && \
			count == ft_lstsize(changes))
				return (ptr->content);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

t_img_data	*get_close_image(t_data *data, int id, t_list *changes)
{
	t_list		*ptr;
	t_img_data	*img;
	int			count;
	int			max;
	t_img_data	*result;

	ptr = data->imgs;
	max = 0;
	result = NULL;
	while (ptr)
	{
		img = ptr->content;
		if (img->id == id)
		{
			count = count_common(changes, img->changes, &is_equal_changes);
			if (count > max && ft_lstsize(img->changes) == count)
			{
				max = count;
				result = img;
			}
		}
		ptr = ptr->next;
	}
	return (result);
}

t_img_data	*alloc_new_image(t_data *data, \
								t_img_data *img_ref, int id, char *path)
{
	t_img_data	*img;
	t_point		a;

	if (!img_ref)
		img = alloc_img(data, id, path);
	else
	{
		img = malloc(sizeof(t_img_data));
		if (!img)
			return (NULL);
		init_canvas(data, img, img_ref->width, img_ref->height);
		a.x = 0;
		a.y = 0;
		image_put(img, img_ref, a, ALL);
		img->changes = ft_lstmap(img_ref->changes, &dup_change, &free);
		img->id = id;
		ft_lstadd_back(&(data->imgs), ft_lstnew(img));
	}
	return (img);
}

t_img_data	*new_image(t_data *data, int id, t_list **changes, char *path)
{
	t_img_data	*img;
	t_img_data	*new_img;
	t_list		*ptr;

	if (!changes || !*changes || !(*changes)->content)
		return (alloc_new_image(data, NULL, id, path));
	merge_changes(changes);
	ptr = *changes;
	if (get_image(data, id, ptr))
		return (get_image(data, id, ptr));
	img = get_close_image(data, id, ptr);
	while (ptr)
	{
		if (!img || !is_in_list(ptr->content, img->changes, &is_equal_changes))
		{
			new_img = alloc_new_image(data, img, id, path);
			if (!new_img)
				return (ft_lstclear(changes, &free), NULL);
			iter_img(data, new_img, ptr->content);
			img = new_img;
		}
		ptr = ptr->next;
	}
	return (new_img);
}
