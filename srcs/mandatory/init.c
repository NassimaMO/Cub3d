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
	char	tmp[2];

	if (fd < 0)
		return (ERR_PARSING);
	i = 0;
	cub->map.tab = ft_calloc(cub->map.height, sizeof(int *));
	while (i < cub->map.height)
		cub->map.tab[i++] = ft_calloc(cub->map.width, sizeof(int));
	str = (ft_bzero(tmp, sizeof(char) * 2), gnl_wraper(fd));
	i = 0;
	while (str)
	{
		j = 0;
		while (str[j])
		{
			tmp[0] = str[j];
			cub->map.tab[i][j] = ft_atoi(tmp);
			j++;
		}
		str = (i++, free(str), gnl_wraper(fd));
	}
	return (close(fd));
}

int	pixel(unsigned char r, unsigned char g, unsigned char b)
{
	int pix;

	pix = 0;
	pix = (r << (8 * 2)) + (g << 8) + b;
	return (pix);
}

int	fill_data(char *path, t_cubdata *cub)
{
	int		fd;
	int		i;
	char	*line;
	char	*texture;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_PARSING);
	line = gnl_wraper(fd);
	i = 0;
	while (line && i < 6)
	{
		texture = ft_strchr(line, '.');
		if (texture)
		{
			if (!ft_strncmp("NO", line, 2))
				new_image(&cub->data, NO, NULL, texture);
			else if (!ft_strncmp("SO", line, 2))
				new_image(&cub->data, SO, NULL, texture);
			else if (!ft_strncmp("WE", line, 2))
				new_image(&cub->data, WE, NULL, texture);
			else if (!ft_strncmp("EA", line, 2))
				new_image(&cub->data, EA, NULL, texture);
			i++;
		}
		else if (!ft_strncmp("F", line, 1))
			cub->f_color = (i++, pixel(ft_atoi(ft_strchr(line, ' ')), \
		ft_atoi(ft_strchr(line, ',') + 1), ft_atoi(ft_strrchr(line, ',') + 1)));
		else if (!ft_strncmp("C", line, 1))
			cub->c_color = (i++, pixel(ft_atoi(ft_strchr(line, ' ')), \
		ft_atoi(ft_strchr(line, ',') + 1), ft_atoi(ft_strrchr(line, ',') + 1)));
		line = (free(line), gnl_wraper(fd));
	}
	if (line)
		free(line);
	return (fill_map(cub, fd));
}
