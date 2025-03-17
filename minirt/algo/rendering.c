/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/11 12:08:41 by aloubry          ###   ########.fr       */
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

#define NB_THREADS 20
#include <pthread.h>

typedef struct s_thread_data
{
	int y_start;
	int y_stop;
	t_img *img;
	t_scene *scene;
	t_precomputed_camera *precomputed;
} t_thread_data;

void *t(void *thread_data)
{
	int y;
	int x;
	t_ray ray;
	t_color color;
	t_thread_data *data;

	data = (t_thread_data*)thread_data;
	y = data->y_start;
	while (y < data->y_stop)
	{
		x = 0;
		while (x < data->img->width)
		{
			ray = get_ray(x, y, data->precomputed);
			color = trace_ray(&ray, data->scene);
			place_pixel_in_mlx_img(data->img, x, y, color);
			x++;
		}
		y++;
	}
	return (NULL);
}

// fills img using rays
static void	fill_img(t_img *img, t_scene *scene)
{
	t_precomputed_camera precomputed = precompute_camera(scene->camera, img);
	int y_step = img->height / NB_THREADS;
	int leftover = img->height % NB_THREADS;
	pthread_t *threads = malloc(sizeof(pthread_t) * NB_THREADS);
	t_thread_data *datas = malloc(sizeof(t_thread_data) * NB_THREADS);
	int i = 0;
	while(i < NB_THREADS)
	{
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
		datas[i].img = img;
		datas[i].scene = scene;
		datas[i].precomputed = &precomputed;
		printf("Thread %d: y_start = %d, y_stop = %d\n", i, datas[i].y_start, datas[i].y_stop);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(&threads[i], NULL, t, (void*)&datas[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// renders scene using mlx image
void	render_scene(t_mrt_data *data)
{
	t_img	*img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!img)
	{
		ft_putstr_fd("mlx_new_image error\n", 2);
		clean_exit(EXIT_FAILURE, data);
	}
	fill_img(img, &data->scene);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
