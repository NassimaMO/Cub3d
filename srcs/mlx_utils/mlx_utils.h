/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmouslim <nmouslim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:40:15 by nghulam-          #+#    #+#             */
/*   Updated: 2023/10/24 18:06:20 by nmouslim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H

# define MLX_UTILS_H

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "X11/keysym.h"
# include <math.h>

# define NUM_PATH "./images/numbers/"
# define FONT_PATH "./images/font/"
# define EXT ".xpm"

# define INT 1
# define CHAR 2

# define TRANSP 1
# define ALL 2

# define RIGHT 1
# define LEFT 2
# define UP 3
# define DOWN 4

# define CLOCKW 1
# define ANTICLOCKW 2

# define START 1
# define MID 2
# define END 3

# define ORIGINAL 1
# define RESIZE 2

# define HOR 1
# define VER 2

typedef struct s_window {
	void	*ptr;
	int		width;
	int		height;
}	t_window;

typedef struct s_data {
	void		*mlx_ptr;
	t_window	win;
	t_list		*canvases;
	t_list		*imgs;
}	t_data;

typedef struct s_img_data {
	void	*ptr;
	void	*mlx_ptr;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		id;
	t_list	*changes;
}	t_img_data;

typedef struct s_changes {
	void	*f;
	int		new_width;
	int		new_height;
	int		canvas_id;
	union {
		int		scale;
		int		color;
		int		direction;
		int		alpha_lvl;
		t_point	start;
	};
}	t_changes;

typedef struct s_param {
	t_data		*data;
	t_img_data	*img;
	t_img_data	*new_img;
	t_img_data	*canvas;
}	t_param;

typedef struct s_font {
	int	x;
	int	y;
	int	size;
	int	color;
}	t_font;

int			mlx_flush_event(t_xvar *xvar);

/* pixel.c */
void		my_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void		background_pix(t_img_data *canvas, int color);
void		background_gradient(t_img_data *canvas, int start, int end, \
															int parameter);
void		image_put(t_img_data *canvas, t_img_data *img, t_point a, int p);
void		put_canvas(t_data *data, int id_src, int id_dest);

/* font.c */
void		put_img_str(t_data *data, char *str, t_font font, \
														t_img_data *canvas);
void		put_img_nbr(t_data *data, int nb, t_font font, t_img_data *canvas);

/* get_image.c */
t_img_data	*get_canvas(t_data *data, int id);
t_img_data	*get_image(t_data *data, int id, t_list *changes);
t_img_data	*get_close_image(t_data *data, int id, t_list *changes);
t_img_data	*alloc_new_image(t_data *data, t_img_data *img_ref, \
											int id, char *path);
t_img_data	*new_image(t_data *data, int id, t_list **changes, \
													char *path);

/* img_changes_utils.c */
int			is_equal_changes(void *struct1, void *struct2);
int			is_same_changes(void *struct1, void *struct2);
void		multisuppr(t_list **list, t_changes ref, int nb);
int			count_common(t_list *list1, t_list *list2, int (f)(void *, void *));

/* iter_img.c */
t_param		transf_p(t_data *data, t_img_data *img, t_img_data *new_img, \
															t_changes *changes);
void		iter_img(t_data *data, t_img_data *img, t_changes *changes);

/* lst_utils.c */
t_list		*is_in_list(void *ptr, t_list *list, int (equal_f)(void *, void *));
void		ft_lstsuppr(t_list **list, t_list *one, void (*del)(void*));
int			count_equal(t_list *list, void *ptr, int (equal_f)(void *, void *));

/* merge_changes.c */
void		merge_changes(t_list **changes);

/* other_changes_func.c */
void		rotate(t_param p, t_changes *changes, int i, int j);
void		invert(t_param p, t_changes *changes, int i, int j);
void		cut(t_param p, t_changes *changes, int i, int j);
void		recolor(t_param p, t_changes *changes, int i, int j);

/* resize.c */
void		resize(t_param p, t_changes *changes, int i, int j);

/* transparency.c */
int			add_color(unsigned int dest, unsigned int src, int alpha_lvl);
int			average_color(int status, unsigned int pixel, int *sum, int *n);
void		alpha(t_param p, t_changes *changes, int i, int j);

/* utils.c */
void		ft_init(int *n1, int *n2, int *n3, int *n4);
t_point		transf_point(int x, int y);
void		center_coord(int *width, int *height, t_img_data *img);

/* input.c */
int			ft_exit(t_data *data);
int			no_input(t_data *data);
int			input_escape(int key, t_data *data);

/* alloc.c */
t_img_data	*alloc_img(t_data *data, int id, char *path);
int			alloc_canvas(t_data *data, int width, int height, int id);
void		*dup_change(void *change);
int			alloc_c(t_list **list, t_changes changes);

/* free_memory.c */
void		free_img(void *p);
void		free_img_list(t_list **list);
void		free_data(t_data *data);

/* init.c */
void		init_img(t_data *data, t_img_data *img, int id, \
													char *path);
int			init_canvas(t_data *data, t_img_data *canvas, \
													int width, int height);
t_changes	transf_c(void (f)(t_param, t_changes *, int, int), \
											const void *p1, int p2, int p3);
t_font		transf_font(int x, int y, int size, int color);

#endif
