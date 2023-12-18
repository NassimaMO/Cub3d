/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:54:11 by nghulam-          #+#    #+#             */
/*   Updated: 2022/11/15 16:54:13 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 0 && str[i - 1] == '\n')
		i--;
	return (i);
}

char	*gnl_trim(int fd, const char *set)
{
	char	*str;
	char	*tmp;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	tmp = ft_strtrim(str, set);
	free(str);
	return (tmp);
}

char	*gnl_wraper(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (ft_strchr(str, '\n'))
		*ft_strchr(str, '\n') = '\0';
	return (str);
}
