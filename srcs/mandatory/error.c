/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:15 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:17 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* give an error code as parameter to print corresponding error message */
int	print_errors(int n)
{
	static int	error = 0;

	if (n == ERR_ARGS && !error)
		error = (ft_printf("Error\nInvalid args.\n"), 1);
	if (n == ERR_PARSING && !error)
		error = (ft_printf("Error\nInvalid map.\n"), 1);
	if (n == ERR_MEMORY && !error)
		error = (ft_printf("Error\nMemory issue.\n"), 1);
	return (n);
}

/* prints the map ; debugging */
void	print_map(t_map *map)
{
	int	i;
	int	j;

	ft_printf("\n");
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->tab[i][j] == -1)
				ft_printf("X");
			else if (ft_isalpha(map->tab[i][j]))
				ft_printf("%c", map->tab[i][j]);
			else
				ft_printf("%d", map->tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}
