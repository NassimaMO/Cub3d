/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:56:48 by nghulam-          #+#    #+#             */
/*   Updated: 2022/10/30 17:56:49 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

char	*path_font(int n)
{
	int		len_path;
	int		len_ext;
	char	*str;

	len_ext = ft_strlen(EXT);
	if (ft_isdigit(n))
		len_path = ft_strlen(NUM_PATH);
	else if (ft_isalpha(n))
		len_path = ft_strlen(FONT_PATH);
	else
		return (NULL);
	str = ft_calloc(len_path + len_ext + 2, 1);
	if (!str)
		return (NULL);
	if (ft_isdigit(n))
		ft_strlcpy(str, NUM_PATH, len_path + 1);
	else if (ft_isalpha(n))
		ft_strlcpy(str, FONT_PATH, len_path + 1);
	ft_strlcpy(str + len_path, (char *)(&n), 2);
	ft_strlcpy(str + len_path + 1, EXT, len_ext + 1);
	return (str);
}

static void	put_img_alnum(t_data *data, char c, t_font *font, \
t_img_data *canvas)
{
	t_img_data	*img;
	t_list		*changes;

	changes = NULL;
	alloc_c(&changes, transf_c(&resize, ORIGINAL, font->size, font->size));
	alloc_c(&changes, transf_c(&recolor, font->color));
	img = new_image(data, c, &changes, &path_font);
	image_put(canvas, img, transf_point(font->x, font->y), TRANSP);
	font->x += img->width;
	ft_lstclear(&changes, &free);
}

static int	font_width(t_data *data, int font_height)
{
	t_img_data	*img;
	t_list		*list;

	list = NULL;
	img = new_image(data, 'A', NULL, &path_font);
	alloc_c(&list, transf_c(&resize, ORIGINAL, img->width, font_height));
	img = new_image(data, 'A', &list, &path_font);
	ft_lstclear(&list, &free);
	return (img->width);
}

void	put_img_str(t_data *data, char *str, t_font font, t_img_data *canvas)
{
	int			i;
	int			start;
	static int	height = 0;

	i = 0;
	start = font.x;
	while (str[i])
	{
		if (str[i] == ' ' && ++i)
			font.x += font_width(data, font.size);
		else if (str[i] == '\n' && ++i)
		{
			font.x = start;
			if (!height)
				height = font.size;
			font.y += height + 10;
		}
		else if (!ft_isalnum(str[i]))
			return ;
		else
			put_img_alnum(data, str[i++], &font, canvas);
	}
}

void	put_img_nbr(t_data *data, int nb, t_font font, t_img_data *canvas)
{
	char	*str;

	str = ft_itoa(nb);
	put_img_str(data, str, font, canvas);
	free(str);
}
