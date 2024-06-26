/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:48:32 by nghulam-          #+#    #+#             */
/*   Updated: 2023/11/02 14:48:35 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "mlx_utils.h"
# include "math.h"

# include <stdio.h>
# include <time.h>
# include <sys/time.h>

# include <X11/keysym.h>

# define WIN_NAME "CUB3D"

# define ERROR -1
# define ERR_MEMORY -2
# define ERR_ARGS -3
# define ERR_PARSING -4

# define MAIN 1
# define FOV 70
# define WALL 1
# define SENS 0.174532925
# define SPEED 0.4

# define EPSILON 10e-5

# define CURRENT 1
# define NEXT 2

typedef struct s_map {
	int	width;
	int	height;
	int	**tab;
}	t_map;

typedef struct s_coord {
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_settings {
	char	fov;
	double	sens;
}	t_settings;

typedef struct s_cam {
	t_coord	dir;
	t_coord	hor;
	t_coord	ver;
}	t_cam;

typedef struct s_player {
	t_coord	pos;
	double	speed;
}	t_player;

typedef struct s_cubdata {
	t_data		data;
	t_map		map;
	t_map		valid_map;
	t_player	player;
	t_cam		cam;
	t_settings	settings;
	int			f_color;
	int			c_color;
}	t_cubdata;

/* error.c */
int		print_errors(int n);
int		check_ext(char *path);

/* init.c */
int		init_data(t_data *data);
int		fill_data(int fd, t_cubdata *cub);

/* input.c */
int		input(int key, t_cubdata *cub);
int		input_move(int key, t_player *player, t_map *map, t_coord direction);
int		input_cam(int key, t_coord *dir, t_cubdata *cub, t_img_data *canvas);

/* memory.c */
int		alloc_map(t_map *map);
void	free_cubdata(t_cubdata *cub);

/* parsing.c */
int		parse_info(char *path, t_cubdata *cub);
int		parse_map_walls(t_map *map);
int		backtracking(t_map *map, int i, int j);

/* utils.c */
char	*strnotsp(char *str);
int		nospacelen(char *str);
t_coord	transf_coord(double x, double y, double z);
t_coord	normalize(t_coord vector, double new_norm);
char	get_orientation(t_coord pint, t_coord vector);
// DEBBUG
void	print_map(t_map *map);
void	print_coord(t_coord *coord);
double	time_diff(struct timespec *start, struct timespec *end);
double	average_time(const char *fname, double time);
void	print_averages(void);

/* raycasting.c */
t_coord	get_case(t_coord vector, t_coord point, int p);
void	raycasting(t_cubdata *cub);
void	new_raycasting(t_cubdata *cub);

#endif
