/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blblblbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 18:46:03 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const t_vector3	g_up = {.x = 0, .y = 1, .z = 0};

float	degrees_to_radians(float degrees)
{
	return (degrees * MRT_PI / 180.0);
}

t_precomputed_camera	precompute_camera(t_camera *camera, t_img *img)
{
	t_precomputed_camera	result;

	result.right_vector = v3_normalize(v3_cross(g_up, camera->direction));
	result.up_vector = v3_cross(camera->direction, result.right_vector);
	result.aspect_ratio = (float)img->width / (float)img->height;
	result.viewport_height = 2 * tan(degrees_to_radians(camera->fov) / 2);
	result.viewport_width = result.aspect_ratio * result.viewport_height;
	return (result);
}

// returns 3d coordinates of a pixel in our world depending on camera
t_vector3	pixel_to_world_coordinates(t_camera *camera, t_precomputed_camera *precomputed_camera, int x, int y)
{
	float		u;
	float		v;
	t_vector3	pixel_world;

	u = (2 * (x + 0.5) / (float)WIDTH - 1) * precomputed_camera->viewport_width / 2;
	v = (1 - 2 * (y + 0.5) / (float)HEIGHT) * precomputed_camera->viewport_height / 2;
	pixel_world = v3_add(v3_add(v3_add(camera->position, v3_scale(precomputed_camera->right_vector, u)), v3_scale(precomputed_camera->up_vector, v)), camera->direction);
	return (pixel_world);
}

// returns ray for pixel x, y with normalized direction
t_ray	get_ray(int x, int y, t_precomputed_camera *precomputed, t_camera *camera)
{
	t_ray	ray;

	ray.origin = camera->position;
	ray.direction = v3_normalize(v3_subtract(pixel_to_world_coordinates(camera, precomputed, x, y), camera->position));
	return (ray);
}

t_color apply_phong(t_scene *scene, t_shape *shape)
{
	t_color color;

	if (shape->type == SPHERE)
		color = shape->data.sphere.color;
	else if (shape->type == PLANE)
		color = shape->data.plane.color;
	else if (shape->type == CYLINDER)
		color = shape->data.cylinder.color;
    color = color_multiply(color, color_scale(scene->ambiant_light->color, scene->ambiant_light->ratio));
	// cast ray towards light and if hit apply diffuse and specular elements
	// apply attenuation depending on range from light ? (bonus bonus)
	return (color);
}

// t = intersection distance
// returns NULL if no intersection
t_shape *get_closest_shape_intersecting(t_ray *ray, t_list *shapes)
{
	t_shape *closest_shape;
	float t;
	float closest_t;

	closest_shape = NULL;
	closest_t = __FLT_MAX__;
	while (shapes)
	{
		t_shape *shape = (t_shape *)shapes->content;
		if (shape->type == SPHERE)
		{
 			// sphere check
		}
		else if (shape->type == PLANE && intersect_plane(ray, &shape->data.plane, &t) && t < closest_t)
		{
			closest_t = t;
			closest_shape = shape;
		}
		else if (shape->type == CYLINDER)
		{
			// cylinder check
		}
		shapes = shapes->next;
	}
	return (closest_shape);
}

t_color trace_ray(t_ray *ray, t_scene *scene)
{
	t_color color;
	t_shape *closest_shape;

	ft_memset(&color, 0, sizeof(t_color));
	closest_shape = get_closest_shape_intersecting(ray, scene->shapes);
	if (closest_shape)
	{
		color = apply_phong(scene, closest_shape);
	}
	return (color);
}

// fills img using rays
void fill_img(t_img *img, t_scene *scene)
{
	t_precomputed_camera precomputed;
	t_ray ray;
	t_color color;
	int x;
	int y;

	precomputed = precompute_camera(scene->camera, img);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ray = get_ray(x, y, &precomputed, scene->camera);
			color = trace_ray(&ray, scene);
			place_pixel_in_mlx_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

// renders scene using mlx image
void render_scene(t_mrt_data *data)
{
	t_img *img;

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