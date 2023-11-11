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

/* moving player with wasd keys input handling */
static int	input_move(int key, t_player *player)
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
	return (0);
}

/* moving camera with arrows input handling */
static int	input_cam(int key, t_coord *direction, t_settings *settings)
{
	if (key == XK_Up)
		direction->z += SENS * settings->sens;
	else if (key == XK_Down)
		direction->z -= SENS * settings->sens;
	else if (key == XK_Left)
	{
		*direction = transf_coord(direction->x * cos(SENS) + direction->y * \
		sin(SENS), -direction->x * sin(SENS) + direction->y * cos(SENS), \
		direction->z);
	}
	else if (key == XK_Right)
	{
		*direction = transf_coord(direction->x * cos(SENS) - direction->y * \
		sin(SENS), direction->x * sin(SENS) + direction->y * cos(SENS), \
		direction->z);
	}
	return (0);
}

/* general function for input handling */
int	input(int key, t_cubdata *cub)
{
	input_escape(key, &cub->data);
	input_move(key, &cub->player);
	input_cam(key, &cub->player.direction, &cub->settings);
	raycasting(cub);
	mlx_flush_event(cub->data.mlx_ptr);
	return (key);
}
