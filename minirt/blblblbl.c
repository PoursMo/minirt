/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blblblbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/23 15:54:49 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_vector3	g_up = {.x = 0, .y = 1, .z = 0};

float	degrees_to_radians(float degrees)
{
	return (degrees * MRT_PI / 180.0);
}

t_precomputed_camera	precompute_camera(t_camera *camera, t_img img)
{
	t_precomputed_camera	result;

	result.right_vector = v3_normalize(v3_cross(g_up, camera->direction));
	result.up_vector = v3_cross(camera->direction, result.right_vector);
	result.aspect_ratio = (float)img.width / (float)img.height;
	result.viewport_height = 2 * tan(degrees_to_radians(camera->fov) / 2);
	result.viewport_width = result.aspect_ratio * result.viewport_height;
	return (result);
}

// returns 3d coordinates of a pixel in our world depending on camera
t_vector3	pixel_to_world_coordinates(t_camera *camera, t_precomputed_camera precomputed_camera, int x, int y)
{
	float		u;
	float		v;
	t_vector3	pixel_world;

	u = (2 * (x + 0.5) / (float)WIDTH - 1) * precomputed_camera.viewport_width / 2;
	v = (1 - 2 * (y + 0.5) / (float)HEIGHT) * precomputed_camera.viewport_height / 2;
	pixel_world = v3_add(v3_add(v3_add(camera->position, v3_scale(precomputed_camera.right_vector, u)), v3_scale(precomputed_camera.up_vector, v)), camera->direction);
	return (pixel_world);
}

// returns normalized vector representing the direction of a ray for a pixel x, y
t_vector3	get_ray(int x, int y, t_precomputed_camera precomputed)
{
	t_vector3	ray;

	ray = v3_normalize(v3_subtract(pixel_to_world_coordinates(get_scene()->camera, precomputed, x, y), get_scene()->camera->position));
	return (ray);
}

// fills img using rays
void fill_img(t_img *img)
{
	t_precomputed_camera precomputed;
	t_ray ray;
	t_color color = {.red = 200, .green = 50, .blue = 100}; // temporary color
	int x;
	int y;

	precomputed = precompute_camera(get_scene()->camera, *img);
	ray.origin = get_scene()->camera->position;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ray.direction = get_ray(x, y, precomputed);
			(void)ray;
			// get color using ray
			place_pixel_in_mlx_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

// renders scene using mlx image
void render_scene(t_mlx_data *data)
{
	t_img *img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!img)
    {
    	printf(" !! KO !!\n");
    	exit(1); // do clean exit
    }
	fill_img(img);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}