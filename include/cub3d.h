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

# include <X11/keysym.h>

# define WIN_NAME "CUB3D"

# define ERROR -1
# define ERR_MEMORY -2
# define ERR_ARGS -3
# define ERR_PARSING -4

# define MAIN 1

# define FOV 90
# define WALL 1
# define SENS 0.174532925

# define RATIOV 0.5
# define RATIOH 0.5

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

typedef struct s_player {
	t_coord	position;
	t_coord	direction;
	double	speed;
}	t_player;

typedef struct s_cubdata {
	t_data		data;
	t_map		map;
	t_map		valid_map;
	int			f_color;
	int			c_color;
	t_player	player;
	t_settings	settings;
}	t_cubdata;

/* error.c */
int		print_errors(int n);
void	print_map(t_map *map);

/* init.c */
void	init_data(t_data *data);
int		fill_data(char *path, t_cubdata *cub);

/* input.c */
int		input(int key, t_cubdata *cub);

/* memory.c */
int		alloc_map(t_map *map);
void	free_cubdata(t_cubdata *cub);

/* parsing.c */
int		parse_info(char *path, t_cubdata *cub);
int		parse_map_walls(t_map *map);
int		backtracking(t_map *map, int i, int j);

/* utils.c */
char	*firstnotsp(char *str);
int		nospacelen(char *str);
t_coord	transf_coord(double x, double y, double z);
void	print_coord(t_coord *coord);

/* raycasting.c */
void	raycasting(t_cubdata *cub);

#endif
