#include "cub3d.h"

void	init_window(t_data *data)
{
	mlx_get_screen_size(data->mlx_ptr, &(data->win.width), \
	&(data->win.height));
	data->win.ptr = \
	mlx_new_window(data->mlx_ptr, data->win.width, data->win.height, WIN_NAME);
	if (data->win.ptr)
		alloc_canvas(data, data->win.width, data->win.height, MAIN);
	else
		return (free_data(data), exit(print_errors(ERR_MEMORY)));
}

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (print_errors(ERR_MEMORY), free_data(data), exit(ERROR));
	init_window(data);
}

int	fill_map(t_cubdata *cub, int fd)
{
	size_t	i;
	int		j;
	char	*str;

	if (fd < 0)
		return (ERR_PARSING);
	i = 0;
	cub->map.tab = malloc(cub->map.height * sizeof(int *));
	while (i < cub->map.height)
		cub->map.tab[i++] = malloc(cub->map.width * sizeof(int));
	str = gnl_wraper(fd);
	i = 0;
	while (str)
	{
		j = 0;
		while (str[j])
		{
			cub->map.tab[i][j] = ft_atoi(str + j);
			j++;
		}
		str = (i++, free(str), gnl_wraper(fd));
	}
	return (close(fd));
}

int	fill_data(char *path, t_cubdata *cub)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_PARSING);
	return (fill_map(cub, fd));
}
