/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:17:18 by nghulam-          #+#    #+#             */
/*   Updated: 2023/12/18 17:17:20 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* give an error code as parameter to print corresponding error message */
int	print_errors(int n)
{
	static int	error = 0;

	if (n == ERR_ARGS && !error)
		error = (ft_printf("Error\nInvalid args.\n"), 1);
	else if (n == ERR_PARSING && !error)
		error = (ft_printf("Error\nInvalid map.\n"), 1);
	else if (n == ERR_MEMORY && !error)
		error = (ft_printf("Error\nMemory issue.\n"), 1);
	else if (n < 0 && !error)
		error = (ft_printf("Error\n"), 1);
	return (n);
}

int	check_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len > 4 && (path[len - 4] != '.' || path[len - 3] != 'c' || \
					path[len - 2] != 'u' || path[len - 1] != 'b'))
		return (ERR_ARGS);
	return (0);
}
