/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:28 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:29 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (print_errors(ERR_MEMORY), free_data(data), exit(ERROR));
	mlx_get_screen_size(data->mlx_ptr, &(data->win.width), \
	&(data->win.height));
	data->win.ptr = \
	mlx_new_window(data->mlx_ptr, data->win.width, data->win.height, WIN_NAME);
	if (data->win.ptr)
		alloc_canvas(data, data->win.width, data->win.height, MAIN);
	else
		return (free_data(data), exit(print_errors(ERR_MEMORY)));
}

static void	init_p(t_player *player, int i, int j, char c)
{
	if (c == 'N')
	{
		player->direction.x = 0;
		player->direction.y = 1;
	}
	if (c == 'S')
	{
		player->direction.x = 0;
		player->direction.y = -1;
	}
	if (c == 'W')
	{
		player->direction.x = -1;
		player->direction.y = 0;
	}
	if (c == 'E')
	{
		player->direction.x = 1;
		player->direction.y = 0;
	}
	player->direction.z = 0;
	player->position.x = j;
	player->position.y = i;
	player->position.z = 0;
}

static int	fill_map(t_cubdata *cub, char *first_line, int fd)
{
	int		i;
	int		j;
	char	*s;
	char	tmp[2];

	if (!first_line || alloc_map(&cub->map))
		return (ERR_PARSING);
	s = (ft_bzero(tmp, 2), ft_bzero(&i, sizeof(int)), first_line);
	while (s)
	{
		j = 0;
		while (i < cub->map.height && s[j])
		{
			tmp[0] = s[j];
			if (s[j] == 'N' || s[j] == 'S' || s[j] == 'W' || s[j] == 'E')
				cub->map.tab[i][j] = (init_p(&cub->player, i, j, s[j]), s[j]);
			else
				cub->map.tab[i][j] = ft_atoi(tmp);
			j++;
		}
		s = (i++, free(s), gnl_wraper(fd));
	}
	return (close(fd));
}

static int	pixel(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(firstnotsp(ft_strchr(str, ' ')));
	g = ft_atoi(ft_strchr(str, ',') + 1);
	b = ft_atoi(ft_strrchr(str, ',') + 1);
	return ((r << (8 * 2)) + (g << 8) + b);
}

int	fill_data(char *path, t_cubdata *cub)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	line = (ft_bzero(&i, sizeof(int)), gnl_wraper(fd));
	while (line && i < 6)
	{
		if (!ft_strncmp("NO", line, 2) && ++i)
			new_image(&cub->data, 'N', NULL, firstnotsp(ft_strchr(line, ' ')));
		else if (!ft_strncmp("SO", line, 2) && ++i)
			new_image(&cub->data, 'S', NULL, firstnotsp(ft_strchr(line, ' ')));
		else if (!ft_strncmp("WE", line, 2) && ++i)
			new_image(&cub->data, 'W', NULL, firstnotsp(ft_strchr(line, ' ')));
		else if (!ft_strncmp("EA", line, 2) && ++i)
			new_image(&cub->data, 'E', NULL, firstnotsp(ft_strchr(line, ' ')));
		else if (!ft_strncmp("F", line, 1) && ++i)
			cub->f_color = pixel(line);
		else if (!ft_strncmp("C", line, 1) && ++i)
			cub->c_color = pixel(line);
		line = (free(line), gnl_wraper(fd));
	}
	while (line && !firstnotsp(line))
		line = (free(line), gnl_wraper(fd));
	return (fill_map(cub, line, fd));
}
