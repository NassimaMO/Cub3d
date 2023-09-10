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
	if (ref->ptr != &invert)
		return ;
	if ((ref->p1 == change->p1) || (change->p1 == RIGHT && ref->p1 == LEFT) || \
		(change->p1 == LEFT && ref->p1 == RIGHT))
		ft_lstsuppr(list, element, &free);
	else if ((change->p1 == UP && ref->p1 == DOWN) || \
	(change->p1 == DOWN && ref->p1 == UP))
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
		if (change->p1 == CLOCKW)
			change->p1 = ANTICLOCKW;
		else if (change->p1 == ANTICLOCKW)
			change->p1 = CLOCKW;
		ft_lstadd_back(list, ft_lstnew(dup_change(change)));
		if (count_equal(*list, ft_lstlast(*list), &is_equal_changes) == 2)
			merge_rotate(change, ft_lstlast(*list), list);
	}
	else if ((change->p1 == CLOCKW && ref->p1 == ANTICLOCKW) || \
	(change->p1 == ANTICLOCKW && ref->p1 == CLOCKW))
		ft_lstsuppr(list, element, &free);
	else
		ft_lstadd_back(list, ft_lstnew(dup_change(change)));
}

static void	merge_change(t_changes *change, t_list *element, t_list **list)
{
	t_changes	*ref;

	ref = element->content;
	if (ref->ptr == &recolor || ref->ptr == &resize)
		*ref = *change;
	else if (ref->ptr == &invert)
		merge_invert(change, element, list);
	else if (ref->ptr == &rotate)
		merge_rotate(change, element, list);
	else if (ref->ptr == &cut)
	{
		ref->p1 = ft_max(2, ref->p1, change->p1);
		ref->p2 = ft_max(2, ref->p2, change->p2);
		ref->p3 = ft_min(2, ref->p3, change->p3);
		ref->p4 = ft_min(2, ref->p4, change->p4);
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
