/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:25:17 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 12:25:19 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (16384);
	return (0);
}