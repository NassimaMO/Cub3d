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
	if (((t_changes *)struct1)->ptr != ((t_changes *)struct2)->ptr)
		return (0);
	if (((t_changes *)struct1)->ptr == &resize && \
		((((t_changes *)struct1)->p1 == ORIGINAL || \
		((t_changes *)struct2)->p1 == ORIGINAL) && \
		(((t_changes *)struct1)->p2 == ((t_changes *)struct2)->p2 || \
		(((t_changes *)struct1)->p2 == ((t_changes *)struct2)->p2))))
		return (1);
	else if (((t_changes *)struct1)->p1 != ((t_changes *)struct2)->p1)
		return (0);
	else if (((t_changes *)struct1)->p2 != ((t_changes *)struct2)->p2)
		return (0);
	else if (((t_changes *)struct1)->p3 != ((t_changes *)struct2)->p3)
		return (0);
	return (1);
}

int	is_same_changes(void *struct1, void *struct2)
{
	if (((t_changes *)struct1)->ptr == ((t_changes *)struct2)->ptr)
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
