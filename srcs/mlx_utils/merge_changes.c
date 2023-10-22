/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:47:23 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:47:24 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	merge_invert(t_changes *change, t_list *element, t_list **list)
{
	t_changes	*ref;

	ref = element->content;
	if (ref->f != &invert)
		return ;
	if (ref->direction == change->direction)
		ft_lstsuppr(list, element, &free);
	else
		ft_lstadd_back(list, ft_lstnew(dup_change(change)));
}

static void	merge_rotate(t_changes *change, t_list *element, t_list **list)
{
	t_changes	*ref;

	ref = element->content;
	if (count_equal(*list, ref, &is_equal_changes) == 2)
	{
		multisuppr(list, *ref, 2);
		if (change->direction == CLOCKW)
			change->direction = ANTICLOCKW;
		else if (change->direction == ANTICLOCKW)
			change->direction = CLOCKW;
		ft_lstadd_back(list, ft_lstnew(dup_change(change)));
		if (count_equal(*list, ft_lstlast(*list), &is_equal_changes) == 2)
			merge_rotate(change, ft_lstlast(*list), list);
	}
	else if ((change->direction == CLOCKW && ref->direction == ANTICLOCKW) \
	|| (change->direction == ANTICLOCKW && ref->direction == CLOCKW))
		ft_lstsuppr(list, element, &free);
	else
		ft_lstadd_back(list, ft_lstnew(dup_change(change)));
}

static void	merge_change(t_changes *change, t_list *element, t_list **list)
{
	t_changes	*ref;

	ref = element->content;
	if (ref->f == &recolor || ref->f == &resize)
		*ref = *change;
	else if (ref->f == &invert)
		merge_invert(change, element, list);
	else if (ref->f == &rotate)
		merge_rotate(change, element, list);
	else if (ref->f == &cut)
	{
		ref->new_width = fmin(ref->new_width, change->new_width);
		ref->new_height = fmin(ref->new_height, change->new_height);
		ref->start.x = fmax(ref->start.x, change->start.x);
		ref->start.y = fmax(ref->start.y, change->start.y);
	}
}

void	merge_changes(t_list **changes)
{
	t_list	*dup_list;
	t_list	*ptr;
	t_list	*change;

	dup_list = NULL;
	change = *changes;
	while (change)
	{
		ptr = is_in_list(change->content, dup_list, &is_same_changes);
		if (!ptr)
			ft_lstadd_back(&dup_list, ft_lstnew(dup_change(change->content)));
		else
			merge_change(change->content, ptr, &dup_list);
		change = change->next;
	}
	ft_lstclear(changes, &free);
	*changes = dup_list;
}
