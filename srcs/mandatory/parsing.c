#include "cub3d.h"

static int	parse_textures(char *line)
{
	static char			*id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	static int			tab[6] = {0};
	int					i;
	static int			bool_end = 0;

	while (ft_isspace(*line))
		line++;
	i = 0;
	while (i < 6)
	{
		if (*line && !ft_strncmp(line, id[i], ft_strlen(id[i])) && \
				ft_isspace(*(line + ft_strlen(id[i]))))
		{
			if (tab[i])
				return (ERR_PARSING);
			tab[i] = (bool_end++, 1);
			break ;
		}
		i++;
	}
	while (*line && (!ft_isspace(*line) || ft_isspace(*(line + 1))))
		line++;
	if (*line && ((i < 4 && open(line + 1, O_RDONLY) < 0) || i == 6))
		return (ERR_PARSING);
	return (bool_end == 6);
}

static int	parse_map_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '0' || line[i] == '1' || line[i] == 'N'\
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		i++;
	if (line[i])
		return (ERR_PARSING);
	return (0);
}

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
	while (line)
	{
		parse = f(line);
		if (parse < 0)
			return (free(line), close(fd), ERR_PARSING);
		if (f == parse_map_char && (size_t)cub->map.width < ft_strlen(line))
			cub->map.width = ft_strlen(line);
		if (f == parse_map_char && !is_all_space(line))
			cub->map.height++;
		if (f == parse_textures && parse == 1)
			f = parse_map_char;
		line = (free(line), gnl_wraper(fd));
	}
	ft_printf("%d\n", cub->map.height);
	return (close(fd));
}

int	parse_walls_1(t_map *map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < (int)map->height - 1)
	{
		j = 0;
		while (j < (int)map->width)
		{
			if (map->tab[i][j] == 1)
			{
				k = j - (j != 0);
				while (j < (int)map->width && map->tab[i][j] == 1)
					j++;
				while (k < j - (j == (int)map->width))
				{
					if (map->tab[i + 1][k] == 1)
						break ;
					k++;
				}
				if (k == j - (j == (int)map->width))
					return (ERR_PARSING);
				break ;
			}
			j++;
		}
		j = (int)map->width - 1;
		while (j >= 0)
		{
			if (map->tab[i][j] == 1)
			{
				k = j + (j != (int)map->width - 1);
				while (j >= 0 && map->tab[i][j] == 1)
					j--;
				while (k > j + (j == -1))
				{
					if (map->tab[i + 1][k] == 1)
						break ;
					k--;
				}
				if (k == j + (j == -1))
					return (ERR_PARSING);
				break ;
			}
			j--;
		}
		i++;
	}
	return (0);
}

int	check_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->tab[i][j] == NO ||
				map->tab[i][j] == SO ||
				map->tab[i][j] == WE ||
				map->tab[i][j] == EA)
				return (bt_player(map, i, j));
			j++;
		}
		i++;
	}
	return (-1);
}

int	bt_player(t_map *map, int i, int j)
{
	if (j + 1 < map->width && map->tab[i][j + 1] == 0)
	{
		map->tab[i][j + 1] = 2;
		if (bt_player(map, i, j + 1))
			return (ERR_PARSING);
	}
	if (j - 1 >= 0 && map->tab[i][j - 1] == 0)
	{
		map->tab[i][j - 1] = 2;
		if (bt_player(map, i, j - 1))
			return (ERR_PARSING);
	}
	if (i + 1 < map->height && map->tab[i + 1][j] == 0)
	{
		map->tab[i + 1][j] = 2;
		if (bt_player(map, i + 1, j))
			return (ERR_PARSING);
	}
	if (i - 1 >= 0 && map->tab[i - 1][j] == 0)
	{
		map->tab[i - 1][j] = 2;
		if (bt_player(map, i - 1, j))
			return (ERR_PARSING);
	}
	if (j + 1 >= map->width || j - 1 < 0 || i + 1 >= map->height || i - 1 < 0)
		return (ERR_PARSING);
	return (0);
}
