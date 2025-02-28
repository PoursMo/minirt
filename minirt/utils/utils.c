/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:39:35 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	place_pixel_in_mlx_img(t_img *img, int x, int y, t_color color)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	if (img->image->byte_order == 0)
	{
		img->data[pixel + 0] = color.blue;
		img->data[pixel + 1] = color.green;
		img->data[pixel + 2] = color.red;
		img->data[pixel + 3] = 0x00;
	}
	else
	{
		img->data[pixel + 0] = 0x00;
		img->data[pixel + 1] = color.red;
		img->data[pixel + 2] = color.green;
		img->data[pixel + 3] = color.blue;
	}
}

t_color	get_pixel_from_mlx_img(t_img *img, int x, int y)
{
	t_color	color;
	int		pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	if (img->image->byte_order == 0)
	{
		color.blue = img->data[pixel + 0];
		color.green = img->data[pixel + 1];
		color.red = img->data[pixel + 2];
	}
	else
	{
		color.red = img->data[pixel + 1];
		color.green = img->data[pixel + 2];
		color.blue = img->data[pixel + 3];
	}
	return (color);
}

void	put_loading_screen(t_mrt_data *data)
{
	int		img_w;
	int		img_h;
	t_img	*img;

	img = mlx_xpm_file_to_image(data->mlx, "loading_img.xpm", &img_w, &img_h);
	if (!img)
	{
		ft_putstr_fd("put_loading_screen error\n", 2);
		clean_exit(EXIT_FAILURE, data);
	}
	mlx_put_image_to_window(data->mlx, data->win, img,
		WIDTH / 2 - img_w / 2, HEIGHT / 2 - img_h / 2);
	mlx_destroy_image(data->mlx, img);
}

int	handle_key(int keycode, void *data)
{
	if (keycode == ESC_KEY)
		mrt_terminate(data);
	return (0);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * MRT_PI / 180.0);
}
