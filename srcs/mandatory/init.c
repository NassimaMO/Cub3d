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

/* initializes all mlx related data */
int	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (free_data(data), ERR_MEMORY);
	if (mlx_get_screen_size(data->mlx_ptr, &(data->win.width), \
	&(data->win.height)))
		return (free_data(data), ERR_MEMORY);
	data->win.ptr = \
	mlx_new_window(data->mlx_ptr, data->win.width, data->win.height, WIN_NAME);
	if (data->win.ptr)
		alloc_canvas(data, data->win.width, data->win.height, MAIN);
	else
		return (free_data(data), ERR_MEMORY);
	return (0);
}

/* initializes player ; give pos and character of player in the file */
static void	init_p(t_cubdata *cub, int i, int j, char c)
{
	t_img_data	*canvas;

	canvas = get_canvas(&cub->data, MAIN);
	if (!canvas)
		return ((void)ft_exit(&cub->data));
	if (c == 'N')
		cub->cam.dir.y = -canvas->width / (2 * tan(cub->settings.fov / 2));
	if (c == 'S')
		cub->cam.dir.y = canvas->width / (2 * tan(cub->settings.fov / 2));
	if (c == 'W')
		cub->cam.dir.x = -canvas->width / (2 * tan(cub->settings.fov / 2));
	if (c == 'E')
		cub->cam.dir.x = canvas->width / (2 * tan(cub->settings.fov / 2));
	cub->cam.hor = transf_coord(-cub->cam.dir.y, cub->cam.dir.x, 0);
	cub->cam.hor = normalize(cub->cam.hor, 1);
	cub->cam.ver.x = -cub->cam.dir.z * cub->cam.dir.x;
	cub->cam.ver.y = -cub->cam.dir.y * cub->cam.dir.z;
	cub->cam.ver.z = pow(cub->cam.dir.y, 2) + pow(cub->cam.dir.x, 2);
	cub->cam.ver = normalize(cub->cam.ver, 1);
	cub->player.pos.x = j + 0.5;
	cub->player.pos.y = i + 0.5;
	cub->player.pos.z = 0.5;
	cub->player.speed = SPEED;
}

/* fills map tab with file data ; should be called after fill_data */
static int	fill_map(t_cubdata *cub, char *first_line, int fd)
{
	int		i;
	int		j;
	char	*s;

	if (!first_line || (alloc_map(&cub->map) && (free(first_line), 1)))
		return (ERR_PARSING);
	i = 0;
	s = first_line;
	while (s)
	{
		j = 0;
		while (s && i < cub->map.height && s[j] && j < cub->map.width)
		{
			cub->map.tab[i][j] = -1;
			if (s[j] == 'N' || s[j] == 'S' || s[j] == 'W' || s[j] == 'E')
				cub->map.tab[i][j] = (init_p(cub, i, j, s[j]), s[j]);
			if ('0' <= s[j] && s[j] <= '9')
				cub->map.tab[i][j] = s[j] - '0';
			j++;
		}
		while (i < cub->map.height && j < cub->map.width)
			cub->map.tab[i][j++] = -1;
		s = (i++, free(s), gnl_wraper(fd));
	}
	return (close(fd), 0);
}

/*	give string starting at color info on file to have corresponding int 
	represented pixel ; string format should be "x r,g,b" 					*/
static int	pixel(char *str, t_cubdata *cub)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;

	tmp = strnotsp(ft_strchr(str, ' '));
	if (!tmp || !*tmp)
		exit((free_cubdata(cub), free(str), print_errors(ERR_PARSING)));
	r = ft_atoi(tmp);
	tmp = ft_strchr(str, ',');
	if (!tmp || !tmp[1])
		exit((free_cubdata(cub), free(str), print_errors(ERR_PARSING)));
	g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	if (!tmp || !tmp[1])
		exit((free_cubdata(cub), free(str), print_errors(ERR_PARSING)));
	b = ft_atoi(tmp + 1);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		exit((free_cubdata(cub), free(str), print_errors(ERR_PARSING)));
	return ((r << (8 * 2)) + (g << 8) + b);
}

/* fills textures, colours and map with file data */
int	fill_data(int fd, t_cubdata *cub)
{
	int			i;
	char		*line;
	t_img_data	*p;

	line = (ft_bzero(&i, sizeof(int)), gnl_trim(fd, " \t\v\f\n\r"));
	while (line && i < 6)
	{
		if ((!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2) || \
			!ft_strncmp("WE", line, 2) || !ft_strncmp("EA", line, 2)) && ++i)
		{
			p = new_image(&cub->data, *line, 0, strnotsp(ft_strchr(line, 32)));
			if (!p)
				return (free(line), ERR_PARSING);
		}
		else if (!ft_strncmp("F", line, 1) && ++i)
			cub->f_color = pixel(line, cub);
		else if (!ft_strncmp("C", line, 1) && ++i)
			cub->c_color = pixel(line, cub);
		while ((i == 6 && line) || (i > 6 && line && !strnotsp(line)))
			line = (free(line), i++, gnl_wraper(fd));
		if (i < 6)
			line = (free(line), gnl_trim(fd, " \t\v\f\n\r"));
	}
	return (fill_map(cub, line, fd));
}
