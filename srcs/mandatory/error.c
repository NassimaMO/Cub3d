#include "cub3d.h"

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

void	print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_printf("%d", map->tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
