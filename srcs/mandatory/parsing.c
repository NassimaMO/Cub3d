/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:52 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:58 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	checks texture line ; should be called at start of file ;
	returns ERR_PARSING on error, 1 if finished and 0 if ongoing ; 
	ERR_PARSING should be negative									*/
static int	parse_textures(char *line)
{
	const char			*id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	const int			tab[6] = {0};
	int					i;
	static int			bool_end = 0;

	while (line && ft_isspace(*line))
		line++;
	i = 0;
	while (line && i < 6)
	{
		if (*line && !ft_strncmp(line, id[i], ft_strlen(id[i])) && \
				ft_isspace(*(line + ft_strlen(id[i]))))
		{
			if (tab[i])
				return (free(line), ERR_PARSING);
			tab[i] = (bool_end++, 1);
			break ;
		}
		i++;
	}
	while (line && *line && (!ft_isspace(*line) || ft_isspace(*(line + 1))))
		line++;
	if (line && *line && ((i < 4 && open(line + 1, O_RDONLY) < 0) || i == 6))
		return (free(line), ERR_PARSING);
	return (free(line), bool_end != 6);
}

/* checks map line ; returns error if an unknown char is found, 0 if not */
static int	parse_map_char(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (ERR_MEMORY);
	while (line[i] == ' ' || line[i] == '0' || line[i] == '1' || line[i] == 'N'\
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		i++;
	if (line[i])
		return (free(line), ERR_PARSING);
	return (free(line), 0);
}

/* parses file and calls check lines functions */
int	parse_info(char *path, t_cubdata *cub)
{
	char	*line;
	int		fd;
	int		parse;
	int		(*f)(char *line);

	f = parse_textures;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_PARSING);
	line = gnl_wraper(fd);
	parse = 1;
	while (line)
	{
		parse = f(ft_strtrim(line, " \t\v\f"));
		if (parse < 0)
			return (free(line), close(fd), ERR_PARSING);
		if (f == parse_map_char && cub->map.width < nospacelen(line))
			cub->map.width = nospacelen(line);
		if (f == parse_map_char && firstnotsp(line))
			cub->map.height++;
		if (f == parse_textures && parse == 0)
			f = parse_map_char;
		line = (free(line), gnl_wraper(fd));
	}
	return (close(fd), parse);
}

int	parse_map_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height && map->tab[i])
	{
		j = 0;
		while (j < map->width && map->tab[i][j] == -1)
			j++;
		if (j != map->width && map->tab[i][j] != 1)
			return (ERR_PARSING);
		while (j < map->width && map->tab[i][j] != -1)
		{
			if (map->tab[i][j] != 1 && (i == 0 || map->tab[i - 1][j] == -1 || \
							i == map->height - 1 || map->tab[i + 1][j] == -1))
				return (ERR_PARSING);
			j++;
		}
		if (j != 0 && j - 1 < map->width && map->tab[i][j - 1] != 1)
			return (ERR_PARSING);
		i++;
	}
	return (0);
}

/* backtracking used to identify reachable cases in the map */
int	backtracking(t_map *map, int i, int j)
{
	if (j + 1 < map->width && map->tab[i][j + 1] == 0)
	{
		map->tab[i][j + 1] = 2;
		if (backtracking(map, i, j + 1))
			return (ERR_PARSING);
	}
	if (j - 1 >= 0 && map->tab[i][j - 1] == 0)
	{
		map->tab[i][j - 1] = 2;
		if (backtracking(map, i, j - 1))
			return (ERR_PARSING);
	}
	if (i + 1 < map->height && map->tab[i + 1][j] == 0)
	{
		map->tab[i + 1][j] = 2;
		if (backtracking(map, i + 1, j))
			return (ERR_PARSING);
	}
	if (i - 1 >= 0 && map->tab[i - 1][j] == 0)
	{
		map->tab[i - 1][j] = 2;
		if (backtracking(map, i - 1, j))
			return (ERR_PARSING);
	}
	return (++j >= map->width || --j < 0 || ++i >= map->height || --i < 0);
}
