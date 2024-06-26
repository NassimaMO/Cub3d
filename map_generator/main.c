/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:06:57 by nghulam-          #+#    #+#             */
/*   Updated: 2023/12/18 15:07:00 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include "libft.h"

/* (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) */
#define S_FLAG 420

void	random_fill(int fd, int player)
{
	static int	count = 0;
	int			random;

	if (count++ == player)
	{
		random = rand() % 4;
		if (random == 0)
			write(fd, "N", 1);
		else if (random == 1)
			write(fd, "S", 1);
		else if (random == 2)
			write(fd, "E", 1);
		else
			write(fd, "W", 1);
		return ;
	}
	if (rand() % 5 == 0)
		write(fd, "1", 1);
	else
		write(fd, "0", 1);
}

void	create_map(int height, int width, int fd)
{
	int	i;
	int	j;
	int	player;

	player = rand() % (height * width - 2 * (height + width - 2));
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width && (i == 0 || i == height - 1))
			j += (write(fd, "1", 1), 1);
		if (j == 0)
			j += (write(fd, "1", 1), 1);
		while (j < width - 1)
		{
			random_fill(fd, player);
			j++;
		}
		if (j == width - 1)
			write(fd, "1", 1);
		write(fd, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc > 3 || !argv[1] || !argv[2] || \
		ft_atoi(argv[1]) < 3 || ft_atoi(argv[2]) < 3)
	{
		write(2, "Error args ; need height and width (integers, >= 3).\n", 53);
		return (EXIT_FAILURE);
	}
	fd = open("../map_generated.cub", O_CREAT | O_RDWR | O_TRUNC, S_FLAG);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (write(2, "Error file.\n", 12), EXIT_FAILURE);
	write(fd, "NO ./pics/colorstone.xpm\n\n", 26);
	write(fd, "SO ./pics/colorstone.xpm\n\n", 26);
	write(fd, "WE ./pics/colorstone.xpm\n\n", 26);
	write(fd, "EA ./pics/colorstone.xpm\n\n", 26);
	write(fd, "F 100,100,100\n\n", 15);
	write(fd, "C 150,150,150\n\n", 15);
	srand(time(NULL));
	create_map(ft_atoi(argv[1]), ft_atoi(argv[2]), fd);
	return (EXIT_SUCCESS);
}
