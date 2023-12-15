/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:50:03 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:50:05 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	returns pointer to string pos where first non-space character is found ;
	returns NULL if str is NULL or empty or contains only spaces */
char	*firstnotsp(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (str);
		str++;
	}
	return (NULL);
}

int	nospacelen(char *str)
{
	int		len;

	if (!firstnotsp(str))
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0 && ft_isspace(str[len]))
		len--;
	return (len + 1);
}

t_coord	transf_coord(double x, double y, double z)
{
	t_coord	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_coord	normalize(t_coord vector, double new_norm)
{
	double	norm;

	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (transf_coord(vector.x * new_norm / norm, \
							vector.y * new_norm / norm, \
							vector.z * new_norm / norm));
}

char	get_orientation(t_coord pint, t_coord vector)
{
	t_coord	_case;
	char	c;

	_case = get_case(vector, pint, CURRENT);
	c = 'W';
	if (fabs(pint.y - _case.y) < EPSILON)
		c = 'S';
	else if (fabs(pint.y - _case.y - 1) < EPSILON)
		c = 'N';
	else if (fabs(pint.x - _case.x) < EPSILON)
		c = 'E';
	return (c);
}

/* DEBUGGING */
/*
void	print_map(t_map *map)
{
	int	i;
	int	j;

	ft_printf("\n");
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->tab[i][j] == -1)
				ft_printf("X");
			else if (ft_isalpha(map->tab[i][j]))
				ft_printf("%c", map->tab[i][j]);
			else
				ft_printf("%d", map->tab[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n");
}

void	print_coord(t_coord *coord)
{
	printf("(%.3f, %.3f, %.3f)", coord->x, coord->y, coord->z);
}

double	time_diff(struct timespec *start, struct timespec *end)
{
	return (1e9 * (end->tv_sec - start->tv_sec) + end->tv_nsec - start->tv_nsec);
}

double	average_time(const char *fname, double time)
{
	static double	sums[10] = {0};
	static int		counts[10] = {0};
	static char		*names[10] = {NULL};

	for (int i = 0 ; i < 10 ; i++)
	{
		if (names[i] && ft_strlen(names[i]) == ft_strlen(fname) && \
						!ft_strncmp(fname, names[i], ft_strlen(names[i])))
		{
			if (time >= 0)
			{
				sums[i] += time;
				counts[i] += 1;
			}
			if (counts[i])
				return (sums[i] / counts[i]);
			return (0);
		}
		else if (!names[i])
			names[i--] = ft_strdup(fname);
	}
	return (0);
}

void	print_averages(void)
{
	double	x;

	x = average_time("new_raycasting", -1);
	printf("average new raycasting time : %dns(%.3fs)\n", (int)x, x * 1e-9);
	x = average_time("intersection", -1);
	printf("average intersection time : %dns(%.3fs)\n", (int)x, x * 1e-9);
	x = average_time("raycasting_put", -1);
	printf("average raycasting_put time : %dns(%.3fs)\n", (int)x, x * 1e-9);
	x = average_time("get_vector", -1);
	printf("average get_vector time : %dns(%.3fs)\n", (int)x, x * 1e-9);
	x = average_time("input_move", -1);
	printf("average input_move time : %dns(%.3fs)\n", (int)x, x * 1e-9);
	x = average_time("input_cam", -1);
	printf("average input_cam time : %dns(%.3fs)\n\n", (int)x, x * 1e-9);
} */
