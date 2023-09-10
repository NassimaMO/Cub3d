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

t_param	transf_p(t_data *data, t_img_data *img, t_img_data *new_img)
{
	t_param	p;

	p.data = data;
	p.img = img;
	p.new_img = new_img;
	return (p);
}

int	get_width(t_img_data *img, t_changes *changes)
{
	if (changes->ptr == &resize)
		return (changes->p2);
	if (changes->ptr == &cut)
		return (changes->p3);
	if (changes->ptr == &rotate)
		return (img->height);
	return (img->width);
}

int	get_height(t_img_data *img, t_changes *changes)
{
	if (changes->ptr == &resize)
		return (changes->p3);
	if (changes->ptr == &cut)
		return (changes->p4);
	if (changes->ptr == &rotate)
		return (img->width);
	return (img->height);
}

void	apply_f(t_param *p, t_changes *changes, int i, int j)
{
	void	(*f)(t_param *, t_changes *, int, int);
	int		width;
	int		height;
	t_list	*old_changes;

	f = changes->ptr;
	width = get_width(p->img, changes);
	height = get_height(p->img, changes);
	old_changes = p->new_img->changes;
	if (i == 0 && j == 0 && changes->ptr != &resize)
	{
		init_canvas(p->data, p->new_img, width, height);
		p->new_img->changes = old_changes;
	}
	(*f)(p, changes, i, j);
}

void	iter_img(t_data *data, t_img_data *img, t_changes *changes)
{
	int			i;
	int			j;
	t_param		p;
	t_img_data	new_img;

	if (!img || !img->ptr)
		return ;
	new_img = *img;
	p = transf_p(data, img, &new_img);
	i = 0;
	while (i < get_height(img, changes))
	{
		j = 0;
		while (j < get_width(img, changes))
		{
			apply_f(&p, changes, i, j);
			j++;
		}
		i++;
	}
	XDestroyImage(((t_img *)(img->ptr))->image);
	free(img->ptr);
	if (img)
		*(img) = (alloc_c(&(new_img.changes), *changes), new_img);
}
