#include "cub3d.h"

void    free_cubdata(t_cubdata *cub)
{
    int i;

    i = 0;
	while (i < cub->map.height)
        free(cub->map.tab[i++]);
    free(cub->map.tab);
}