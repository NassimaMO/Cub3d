#include "cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f' || c == '\n')
		return (1);
	return (0);
}

int	parse_textures(char *line)
{
	static char			*id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	static int			tab[6] = {0};
	int					i;
	static int			bool_end = 0;

	if (line[0] && line[0] != '\n')
	{
		while (ft_isspace(*line))
			line++;
		i = 0;
		while (i < 6)
		{
			if (!ft_strncmp(line, id[i], ft_strlen(id[i])) && ft_isspace(*(line + ft_strlen(id[i]))))
			{
				if (tab[i])
					return (ERR_PARSING);
				tab[i] = (bool_end++, 1);
				break;
			}
			i++;
		}
		while (!ft_isspace(*line))
			line++;
		while (ft_isspace(*line))
			line++;
		if (i < 4 && open(line, O_RDONLY) < 0)
			return (ERR_PARSING);
		if (i == 6)
			return (ERR_PARSING);
	}
	return (bool_end == 6);
}

int	parse_map_wall(t_cubdata *cub, char *path)
{
	int	i;
	int	fd;
	char *str;

	i = 0;
	cub->map.tab = malloc(cub->map.height * sizeof(int *));
	while (i < cub->map.height)
		cub->map.tab[i++] = malloc(cub->map.width * sizeof(int));
	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i = 0;
		while (str[i])
		{
			cub->map.tab[i] = ft_atoi(str[i++]);
		}
	}
}

int	parse_map_char(char *line, t_cubdata *cub)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '0' || line[i] == '1' || line[i] == 'N' \
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
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
		if (f == parse_textures && parse == 1)
			f = parse_map;
		if (f == parse_map)
		{
			if (cub->map.width < ft_strlen(line))
				cub->map.width = ft_strlen(line);
			cub->map.height++;
		}
		line = (free(line), gnl_wraper(fd));
	}
	return (close(fd), 0);
}