/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:52:19 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:52:20 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_param	transf_p(t_data *data, t_img_data *img, t_img_data *new_img, \
															t_changes *changes)
{
	t_param	p;

	p.data = data;
	p.img = img;
	p.new_img = new_img;
	if (changes->f == &alpha)
		p.canvas = get_canvas(data, changes->canvas_id);
	else
		p.canvas = NULL;
	return (p);
}

void	correct_changes(t_img_data *img, t_changes *c)
{
	if (c->f == &resize && c->scale == ORIGINAL)
	{
		if (c->new_width == fmin(c->new_width, \
		(img->width * c->new_height) / img->height))
			c->new_height = (img->height * c->new_width) / img->width;
		else
			c->new_width = (img->width * c->new_height) / img->height;
	}
	if (c->f == &rotate)
	{
		c->new_height = img->width;
		c->new_width = img->height;
	}
	if (!c->new_width)
		c->new_width = img->width;
	if (!c->new_height)
		c->new_height = img->height;
}

void	iter_img(t_data *data, t_img_data *img, t_changes *changes)
{
	int			i;
	int			j;
	t_img_data	new_img;
	void		(*f)(t_param, t_changes *, int, int);

	if (!img || !img->ptr)
		return ;
	correct_changes(img, changes);
	init_canvas(data, &new_img, changes->new_width, changes->new_height);
	new_img.id = img->id;
	i = 0;
	f = changes->f;
	while (i < changes->new_height)
	{
		j = 0;
		while (j < changes->new_width)
		{
			(*f)(transf_p(data, img, &new_img, changes), changes, i, j);
			j++;
		}
		i++;
	}
	new_img.changes = (alloc_c(&(img->changes), *changes), img->changes);
	*img = (mlx_destroy_image(data->mlx_ptr, img->ptr), new_img);
}
