/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:43 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:45 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* frees pointers tab up to size */
static void	free_tab(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* alloc map tab ; map height and width should be initialized beforehand */
int	alloc_map(t_map *map)
{
	int	i;

	i = 0;
	map->tab = ft_calloc(map->height, sizeof(int *));
	if (!map->tab)
		return (ERR_MEMORY);
	while (i < map->height)
	{
		map->tab[i] = ft_calloc(map->width, sizeof(int));
		if (!map->tab[i])
			return (free_tab(map->tab, i), ERR_MEMORY);
		i++;
	}
	return (0);
}

/* frees all data */
void	free_cubdata(t_cubdata *cub)
{
	if (cub->map.tab)
		free_tab(cub->map.tab, cub->map.height);
	free_data(&cub->data);
}
