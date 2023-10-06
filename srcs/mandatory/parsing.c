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
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = 0;
		if (i < 4 && open(line, O_RDONLY) < 0)
			return (ERR_PARSING);
		if (i == 6)
			return (ERR_PARSING);
	}
	return (bool_end == 6);
}

int	parse_map(char *line)
{
	(void)line;
	return (0);
}

int	parse_info(char *path)
{
	char	*line;
	int		fd;
	int		parse;
	int		(*f)(char *line);

	f = parse_textures;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR_PARSING);
	line = get_next_line(fd);
	while (line)
	{
		parse = f(line);
		if (parse < 0)
			return (free(line), close(fd), ERR_PARSING);
		if (f == parse_textures && parse == 1)
			f = parse_map;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}