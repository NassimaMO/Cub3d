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
	double norm;

	norm = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (transf_coord(vector.x * new_norm / norm, \
							 vector.y * new_norm / norm, \
							 vector.z * new_norm / norm));
}

/* DEBUGGING */
void	print_coord(t_coord *coord)
{
	printf("(%.3f, %.3f, %.3f)", coord->x, coord->y, coord->z);
}

double	time_diff(struct timespec *start, struct timespec *end)
{
	return (1e9 * (end->tv_sec - start->tv_sec) + end->tv_nsec - start->tv_nsec);
}

double	average_time(const char *fname, double time, double nb)
{
	static double	*tabs[10] = {NULL};
	static char		*names[10] = {NULL};
	double			average;
	int				i;
	int				j;
	int				k;

	if ((!ft_strncmp(fname, "free", 4)))
	{
		for (i = 0 ; i < 10 ; i++)
		{
			if (tabs[i])
				free(tabs[i]);
			if (names[i])
				free(names[i]);
		}
		return (0);
	}
	average = 0;
	for (i = 0 ; i < 10 ; i++)
	{
		if (names[i] && !ft_strncmp(fname, names[i], ft_strlen(names[i])))
		{
			if (!tabs[i])
			{
				tabs[i] = malloc(nb * sizeof(double));
				for (k = 0 ; k < nb ; k++)
					tabs[i][k] = -1;
			}
			for (j = 0 ; j < nb ; j++)
			{
				if (tabs[i][j] < 0)
				{
					if (time >= 0)
						tabs[i][j] = time;
					break ;
				}
				average += tabs[i][j];
			}
			break ;
		}
		else if (!names[i])
			names[i--] = ft_strdup(fname);
	}
	if (!j)
		return (0);
	return (average / j);
}

void	print_averages(void)
{
	double	x;

	x = average_time("raycasting", -1, 10);
	printf("average raycasting time : %.0fns(%fs)\n", x, x * 1e-9);
	x = average_time("intersection", -1, 10);
	printf("average intersection time : %dns(%fs)\n", (int)x, x * 1e-9);
	x = average_time("raycasting_put", -1, 10);
	printf("average raycasting_put time : %dns(%fs)\n", (int)x, x * 1e-9);
	x = average_time("get_vector", -1, 10);
	printf("average get_vector time : %dns(%fs)\n", (int)x, x * 1e-9);
	x = average_time("input_move", -1, 10);
	printf("average input_move time : %dns(%fs)\n", (int)x, x * 1e-9);
	x = average_time("input_cam", -1, 10);
	printf("average input_cam time : %dns(%fs)\n", (int)x, x * 1e-9);
}
