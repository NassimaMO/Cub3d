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
