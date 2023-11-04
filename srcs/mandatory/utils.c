/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:50:03 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:50:05 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	returns pointer to string pos where first non-space character is found ;
	returns NULL if str is NULL or empty or contains only spaces */
char	*firstnotsp(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (str);
		str++;
	}
	return (NULL);
}

t_coord	transf_coord(int x, int y, int z)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}
