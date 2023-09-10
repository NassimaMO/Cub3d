/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:43:49 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:43:51 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_list	*is_in_list(void *ptr, t_list *list, int (equal_f)(void *, void *))
{
	while (list)
	{
		if (equal_f(ptr, list->content))
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	ft_lstsuppr(t_list **list, t_list *one, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*ptr;

	tmp = NULL;
	ptr = *list;
	while (ptr)
	{
		if (ptr == one)
		{
			if (!tmp)
				*list = ptr->next;
			else
				tmp->next = ptr->next;
			return (ft_lstdelone(ptr, del));
		}
		tmp = ptr;
		ptr = ptr->next;
	}
}

int	count_equal(t_list *list, void *ptr, int (equal_f)(void *, void *))
{
	int	count;

	count = 0;
	while (list)
	{
		if (equal_f(list->content, ptr))
			count++;
		list = list->next;
	}
	return (count);
}
