/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/19 11:18:44 by aloubry          ###   ########.fr       */
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

static void	*thread_routine(void *thread_data)
{
	int				y;
	int				x;
	t_ray			ray;
	t_color			color;
	t_thread_data	*data;

	data = (t_thread_data *)thread_data;
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
	pthread_t				threads[NB_THREADS];
	t_thread_data			datas[NB_THREADS];
	int						i;
	t_precomputed_camera	precomputed;

	precomputed = precompute_camera(scene->camera, img);
	fill_thread_datas(datas, img, scene, &precomputed);
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(&threads[i], NULL, thread_routine, (void *)&datas[i]);
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
