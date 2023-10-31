#include "cub3d.h"

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

void	free_cubdata(t_cubdata *cub)
{
	if (cub->map.tab)
		free_tab(cub->map.tab, cub->map.height);
	free_data(&cub->data);
}
