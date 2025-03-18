/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/18 12:07:02 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*routine(void *thread_data)
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
	pthread_t				*threads;
	t_thread_data			*datas;
	int						i;

	threads = malloc(sizeof(pthread_t) * NB_THREADS);
	if (!threads)
	{
		perror("fill_img");
		return ;
	}
	datas = generate_thread_data(img, scene);
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(&threads[i], NULL, routine, (void *)&datas[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(datas);
	free(threads);
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
