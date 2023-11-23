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

/* checking if point coordinates is inside wall, returns 1 if it's the case ; 
	changes player position and returns 0 if not */
int	check_collide(t_map *map, t_player *player, t_coord point)
{
	t_coord	_case;

	_case = get_case(player->direction, point, CURRENT);
	if (map->tab[(int)_case.x][(int)_case.y] == WALL)
		return (1);
	player->position = point;
	return (0);
}

/* moving player with wasd keys input handling */
int	input_move(int key, t_player *player, t_map *map)
{
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;
	int		value;

	clock_gettime(CLOCK_REALTIME, &start);
	if (key == XK_W || key == XK_w)
	{
		value = !check_collide(map, player, transf_coord(player->position.x + \
		player->direction.x * player->speed, player->position.y + \
		player->direction.y * player->speed, player->position.z));
		clock_gettime(CLOCK_REALTIME, &end);
		//printf("input_move : %f seconds\n", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_A || key == XK_a)
	{
		value = !check_collide(map, player, transf_coord(player->position.x + \
		player->direction.y * player->speed, player->position.y - \
		player->direction.x * player->speed, player->position.z));
		clock_gettime(CLOCK_REALTIME, &end);
		//printf("input_move : %f seconds\n", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_S || key == XK_s)
	{
		value = !check_collide(map, player, transf_coord(player->position.x - \
		player->direction.x * player->speed, player->position.y - \
		player->direction.y * player->speed, player->position.z));
		clock_gettime(CLOCK_REALTIME, &end);
		//printf("input_move : %f seconds\n", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_D || key == XK_d)
	{
		value = !check_collide(map, player, transf_coord(player->position.x - \
		player->direction.y * player->speed, player->position.y + \
		player->direction.x * player->speed, player->position.z));
		clock_gettime(CLOCK_REALTIME, &end);
		//printf("input_move : %f seconds\n", time_diff(&start, &end));
		return (value);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	//printf("input_move : %f seconds\n", time_diff(&start, &end));
	return (0);
}

/* moving camera with arrows input handling */
int	input_cam(int key, t_coord *direction, t_settings *settings)
{
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;

	clock_gettime(CLOCK_REALTIME, &start);
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
	else
	{
		clock_gettime(CLOCK_REALTIME, &end);
		//printf("input_cam : %f seconds\n", time_diff(&start, &end));
		return (0);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	//printf("input_cam : %f seconds\n", time_diff(&start, &end));
	return (1);
}

/* general function for input handling */
int	input(int key, t_cubdata *cub)
{
	if (input_escape(key, &cub->data))
		return (1);
	if (input_move(key, &cub->player, &cub->map) || \
		input_cam(key, &cub->player.direction, &cub->settings))
		return (raycasting(cub), mlx_flush_event(cub->data.mlx_ptr), 1);
	return (0);
}
