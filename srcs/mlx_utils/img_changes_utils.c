/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_changes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:41:48 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:41:50 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	is_equal_changes(void *struct1, void *struct2)
{
	t_changes	*c1;
	t_changes	*c2;
	void		(*f)(t_param, t_changes *, int, int);
	void		(*f2)(t_param, t_changes *, int, int);

	c1 = struct1;
	c2 = struct2;
	f = c1->f;
	f2 = c2->f;
	if (f != f2)
		return (0);
	if (c1->new_width != c2->new_width)
		return (0);
	if (c1->new_height != c2->new_height)
		return (0);
	if (f == &resize && c1->scale != c2->scale)
		return (0);
	if (f == &cut && (c1->start.x != c2->start.x || c1->start.y != c2->start.y))
		return (0);
	if (f == &recolor && c1->color != c2->color)
		return (0);
	if ((f == &invert || f == &rotate) && c1->direction != c2->direction)
		return (0);
	return (1);
}

int	is_same_changes(void *struct1, void *struct2)
{
	if (((t_changes *)struct1)->f == ((t_changes *)struct2)->f)
		return (1);
	return (0);
}

void	multisuppr(t_list **list, t_changes ref, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		ft_lstsuppr(list, is_in_list(&ref, *list, &is_equal_changes), &free);
		i++;
	}
}

int	count_common(t_list *list1, t_list *list2, int (f)(void *, void *))
{
	int	count;

	count = 0;
	while (list1)
	{
		if (is_in_list(list1->content, list2, f) != NULL)
			count++;
		list1 = list1->next;
	}
	return (count);
}
