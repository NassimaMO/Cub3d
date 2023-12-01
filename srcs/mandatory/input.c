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
	t_coord	tmp;

	tmp = transf_coord(point.x - 0.01, point.y - 0.01, point.z - 0.01);
	_case = get_case(player->direction, tmp, CURRENT);
	if (_case.y >= map->height || _case.x >= map->width || \
			map->tab[(int)_case.y][(int)_case.x] == WALL)
		return (1);
	tmp = transf_coord(point.x + 0.01, point.y + 0.01, point.z + 0.01);
	_case = get_case(player->direction, tmp, CURRENT);
	if (_case.y >= map->height || _case.x >= map->width || \
			map->tab[(int)_case.y][(int)_case.x] == WALL)
		return (1);
	player->position = point;
	return (0);
}

/* moving player with wasd keys input handling */
int	input_move(int key, t_player *player, t_map *map, t_coord direction)
{
	int		value;
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;
	clock_gettime(CLOCK_REALTIME, &start);

	if (key == XK_W || key == XK_w)
	{
		value = !check_collide(map, player, transf_coord(player->position.x + \
		direction.x * player->speed, player->position.y + \
		direction.y * player->speed, player->position.z));
		//printf("input : move forward\n");
		clock_gettime(CLOCK_REALTIME, &end);
		average_time("input_move", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_A || key == XK_a)
	{
		value = !check_collide(map, player, transf_coord(player->position.x + \
		direction.y * player->speed, player->position.y - \
		direction.x * player->speed, player->position.z));
		//printf("input : move left\n");
		clock_gettime(CLOCK_REALTIME, &end);
		average_time("input_move", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_S || key == XK_s)
	{
		value = !check_collide(map, player, transf_coord(player->position.x - \
		direction.x * player->speed, player->position.y - \
		direction.y * player->speed, player->position.z));
		//printf("input : move backward\n");
		clock_gettime(CLOCK_REALTIME, &end);
		average_time("input_move", time_diff(&start, &end));
		return (value);
	}
	if (key == XK_D || key == XK_d)
	{
		value = !check_collide(map, player, transf_coord(player->position.x - \
		direction.y * player->speed, player->position.y + \
		direction.x * player->speed, player->position.z));
		//printf("input : move right\n");
		clock_gettime(CLOCK_REALTIME, &end);
		average_time("input_move", time_diff(&start, &end));
		return (value);
	}
	//printf("input : move other\n");
	clock_gettime(CLOCK_REALTIME, &end);
	average_time("input_move", time_diff(&start, &end));
	return (0);
}

/* moving camera with arrows input handling (using spherical coordinates)*/
int	input_cam(int key, t_coord *direction, t_settings *settings, t_img_data *canvas)
{
	double			norm;
	double			angle_hor;
	double			angle_ver;
	/* DEBUGGING */
	struct timespec	start;
	struct timespec	end;
	clock_gettime(CLOCK_REALTIME, &start);

	norm = sqrt(pow(direction->x, 2) + pow(direction->y, 2) + pow(direction->z, 2));
	angle_hor = atan2(direction->y, direction->x);
	angle_ver = asin(direction->z / norm);
	if (key == XK_Up)
	{
		angle_ver += SENS * settings->sens;
		/* printf("input : cam up\n"); */
	}
	else if (key == XK_Down)
	{
		angle_ver -= SENS * settings->sens;
		/* printf("input : cam down\n"); */
	}
	else if (key == XK_Right)
	{
		angle_hor += SENS * settings->sens;
		/* printf("input : cam right\n"); */
	}
	else if (key == XK_Left)
	{
		angle_hor -= SENS * settings->sens;
		/* printf("input : cam left\n"); */
	}
	else
	{
		//printf("input : other\n");
		return (0);
	}
	if (angle_ver > M_PI / 2.0)
		angle_ver = M_PI / 2.0;
	if (angle_ver < -M_PI / 2.0)
		angle_ver = -M_PI / 2.0;
	direction->x = norm * cos(angle_ver) * cos(angle_hor);
	direction->y = norm * cos(angle_ver) * sin(angle_hor);
	direction->z = norm * sin(angle_ver);
	*direction = normalize(*direction, canvas->width / (2 * tan(settings->fov / 2)));
	clock_gettime(CLOCK_REALTIME, &end);
	average_time("input_cam", time_diff(&start, &end));
	return (1);
}

/* general function for input handling */
int	input(int key, t_cubdata *cub)
{
	t_coord	direction;

	if (input_escape(key, &cub->data))
		return (1);
	direction = normalize(cub->player.direction, 1);
	if (input_move(key, &cub->player, &cub->map, direction) || \
		input_cam(key, &cub->player.direction, &cub->settings, \
					get_canvas(&cub->data, MAIN)))
		return (raycasting(cub), mlx_flush_event(cub->data.mlx_ptr), print_averages(), 1);
	return (0);
}
