/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:41 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/18 12:05:32 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_precomputed_camera	precompute_camera(t_camera *camera, t_img *img)
{
	t_precomputed_camera	result;

	result.forward_vector = camera->direction;
	result.origin = camera->position;
	result.right_vector = v3_normalize(v3_cross(v3_up(), camera->direction));
	result.up_vector = v3_cross(camera->direction, result.right_vector);
	result.aspect_ratio = (float)img->width / (float)img->height;
	result.viewport_height = 2 * tan(degrees_to_radians(camera->fov) / 2);
	result.viewport_width = result.aspect_ratio * result.viewport_height;
	return (result);
}

static void	fill_thread_data(t_thread_data *datas, int i, int y_step,
	int leftover)
{
	if (i == 0)
		datas[i].y_stop = y_step;
	else
		datas[i].y_stop = datas[i - 1].y_stop + y_step;
	if (leftover)
	{
		datas[i].y_stop++;
		leftover--;
	}
	if (i == 0)
		datas[i].y_start = 0;
	else
		datas[i].y_start = datas[i - 1].y_stop;
}

t_thread_data	*generate_thread_data(t_img *img, t_scene *scene)
{
	int						y_step;
	int						leftover;
	t_precomputed_camera	precomputed;
	t_thread_data			*datas;
	int						i;

	datas = malloc(sizeof(t_thread_data) * NB_THREADS);
	if (!datas)
		return (perror("generate_thread_data"), NULL);
	y_step = img->height / NB_THREADS;
	leftover = img->height % NB_THREADS;
	precomputed = precompute_camera(scene->camera, img);
	i = 0;
	while (i < NB_THREADS)
	{
		fill_thread_data(datas, i, y_step, leftover);
		datas[i].img = img;
		datas[i].scene = scene;
		datas[i].precomputed = &precomputed;
		i++;
	}
	return (datas);
}
