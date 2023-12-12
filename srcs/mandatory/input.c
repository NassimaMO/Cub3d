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
int	check_collide(t_map *map, t_player *player, t_coord point, \
															t_coord direction)
{
	t_coord	_case;
	t_coord	tmp;

	tmp = transf_coord(point.x - 0.01, point.y - 0.01, point.z - 0.01);
	_case = get_case(direction, tmp, CURRENT);
	if (_case.y >= map->height || _case.x >= map->width || _case.y < 0 || \
	_case.x < 0 || map->tab[(int)_case.y][(int)_case.x] == WALL)
		return (1);
	tmp = transf_coord(point.x + 0.01, point.y + 0.01, point.z + 0.01);
	_case = get_case(direction, tmp, CURRENT);
	if (_case.y >= map->height || _case.x >= map->width || _case.y < 0 || \
	_case.x < 0 || map->tab[(int)_case.y][(int)_case.x] == WALL)
		return (1);
	player->pos = point;
	return (0);
}

/* moving player with wasd keys input handling */
int	input_move(int key, t_player *player, t_map *map, t_coord direction)
{
	if (key == XK_W || key == XK_w)
		return (!check_collide(map, player, transf_coord(player->pos.x + \
		direction.x * player->speed, player->pos.y + \
		direction.y * player->speed, player->pos.z), direction));
	if (key == XK_A || key == XK_a)
		return (!check_collide(map, player, transf_coord(player->pos.x + \
		direction.y * player->speed, player->pos.y - \
		direction.x * player->speed, player->pos.z), direction));
	if (key == XK_S || key == XK_s)
		return (!check_collide(map, player, transf_coord(player->pos.x - \
		direction.x * player->speed, player->pos.y - \
		direction.y * player->speed, player->pos.z), direction));
	if (key == XK_D || key == XK_d)
		return (!check_collide(map, player, transf_coord(player->pos.x - \
		direction.y * player->speed, player->pos.y + \
		direction.x * player->speed, player->pos.z), direction));
	return (0);
}

/* moving camera with arrows input handling (using spherical coordinates)*/
int	input_cam(int key, t_coord *dir, t_cubdata *cub, t_img_data *canvas)
{
	double	norm;
	double	angle_h;
	double	angle_v;

	norm = sqrt(pow(dir->x, 2) + pow(dir->y, 2) + pow(dir->z, 2));
	angle_h = atan2(dir->y, dir->x);
	angle_v = asin(dir->z / norm);
	if (key == XK_Up && angle_v + SENS * cub->settings.sens < M_PI / 2)
		angle_v += SENS * cub->settings.sens;
	else if (key == XK_Down && angle_v - SENS * cub->settings.sens > -M_PI / 2)
		angle_v -= SENS * cub->settings.sens;
	else if (key == XK_Right && angle_v + SENS * cub->settings.sens < M_PI / 2)
		angle_h += SENS * cub->settings.sens;
	else if (key == XK_Left && angle_v - SENS * cub->settings.sens > -M_PI / 2)
		angle_h -= SENS * cub->settings.sens;
	else
		return (0);
	*dir = transf_coord(norm * cos(angle_v) * cos(angle_h), \
			norm * cos(angle_v) * sin(angle_h), norm * sin(angle_v));
	*dir = normalize(*dir, canvas->width / (2 * tan(cub->settings.fov / 2)));
	cub->cam.hor = transf_coord(-cub->cam.dir.y, cub->cam.dir.x, 0);
	cub->cam.hor = normalize(cub->cam.hor, 1);
	return (1);
}

/* general function for input handling */
int	input(int key, t_cubdata *cub)
{
	if (input_escape(key, &cub->data))
		return (1);
	if (input_move(key, &cub->player, &cub->map, normalize(cub->cam.dir, 1)) || \
		input_cam(key, &cub->cam.dir, cub, get_canvas(&cub->data, MAIN)))
		return (new_raycasting(cub), mlx_flush_event(cub->data.mlx_ptr), 1);
	return (0);
}
