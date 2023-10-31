#include "cub3d.h"

int	fns(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (-1);
}
