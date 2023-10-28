#include "cub3d.h"

void	free_cubdata(t_cubdata *cub)
{
	int	i;

	i = 0;
	if (cub->map.tab)
	{
		while (i < cub->map.height)
		{
			if (cub->map.tab[i])
				free(cub->map.tab[i++]);
		}
		free(cub->map.tab);
	}
	free_data(&cub->data);
}
