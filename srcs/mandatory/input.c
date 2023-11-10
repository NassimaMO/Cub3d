/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:49:36 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:37 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	input_move(int key, t_player *player)
{
	if (key == XK_W || key == XK_w)
	{
		player->position.x += player->direction.x * player->speed;
		player->position.y += player->direction.y * player->speed;
	}
	else if (key == XK_A || key == XK_a)
	{
		player->position.x += player->direction.y * player->speed;
		player->position.y -= player->direction.x * player->speed;
	}
	else if (key == XK_S || key == XK_s)
	{
		player->position.x += -player->direction.x * player->speed;
		player->position.y += -player->direction.y * player->speed;
	}
	else if (key == XK_D || key == XK_d)
	{
		player->position.x -= player->direction.y * player->speed;
		player->position.y += player->direction.x * player->speed;
	}
	return(0);
}

int	input_cam(int key, t_cubdata *cub)
{
	if (key == XK_Up)
	{
		cub->player.direction.z += SENS * cub->settings.sens;
	}
	else if (key == XK_Down)
	{
		cub->player.direction.z -= SENS * cub->settings.sens;
	}
	else if (key == XK_Left)
	{
		cub->player.direction.x += SENS * cub->settings.sens;
		cub->player.direction.y -= SENS * cub->settings.sens;
	}
	else if (key == XK_Right)
	{
		cub->player.direction.x -= SENS * cub->settings.sens;
		cub->player.direction.y += SENS * cub->settings.sens;
	}
	return (0);
	
}

/* general function for input handling */
int	input(int key, t_cubdata *cub)
{
	static int	k = 0;

	input_escape(key, &cub->data);
	input_move(key, &cub->player);
	input_cam(key, cub);
	/* if (k == 2)
		 */raycasting(cub);
	k++;
	return (key);
}
