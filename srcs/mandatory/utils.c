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

int	nospacelen(char *str)
{
	int		len;

	if (!firstnotsp(str))
		return (0);
	len = ft_strlen(str) - 1; 
	while (len >= 0 && ft_isspace(str[len]))
		len--;
	return (len + 1);
}

t_coord	transf_coord(double x, double y, double z)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

void	print_coord(t_coord *coord)
{
	printf("(%.3f, %.3f, %.3f)", coord->x, coord->y, coord->z);
}
