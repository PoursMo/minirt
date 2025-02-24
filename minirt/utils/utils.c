/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 18:52:10 by aloubry          ###   ########.fr       */
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

void	clean_exit(int status, t_mrt_data *data)
{
	free_scene(&data->scene);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}

int	mrt_terminate(void *data)
{
	t_mrt_data	*mrt_data;

	mrt_data = (t_mrt_data *)data;
	clean_exit(EXIT_SUCCESS, mrt_data);
	return (0);
}

int	handle_key(int keycode, void *data)
{
	if (keycode == ESC_KEY)
		mrt_terminate(data);
	return (0);
}

void	free_scene(t_scene *scene)
{
	if (scene->ambiant_light)
		free(scene->ambiant_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
	if (scene->shapes)
		ft_lstclear(&scene->shapes, free);
}
