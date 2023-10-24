#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "mlx_utils.h"

# include <stdio.h>

# include <X11/keysym.h>

# define WIN_NAME "CUB3D"

# define ERROR -1
# define ERR_MEMORY -2
# define ERR_ARGS -3
# define ERR_PARSING -4

# define NO 1
# define SO 2
# define WE 3
# define EA 4

# define MAIN 1

typedef struct s_map {
	size_t	width;
	size_t	height;
	int		**tab;
}	t_map;

typedef struct s_cubdata {
	t_data	data; 
	t_map	map;
	int		f_color;
	int		c_color;
}	t_cubdata;

/* init.c */
void	init_window(t_data *data);
void	init_data(t_data *data);
int		fill_data(char *path, t_cubdata *cub);

/* input.c */
int		input(int key, t_data *data);

/* error.c */
int		print_errors(int n);
void	print_map(t_map *map);

/* parsing.c */
int		parse_info(char *path, t_cubdata *cub);

/* free.c */
void	free_cubdata(t_cubdata *cub);

#endif