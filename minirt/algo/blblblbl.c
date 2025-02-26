/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blblblbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/26 17:11:52 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * MRT_PI / 180.0);
}

t_precomputed_camera	precompute_camera(t_camera *camera, t_img *img)
{
	t_precomputed_camera	result;

	result.right_vector = v3_normalize(v3_cross(v3_up(), camera->direction));
	result.up_vector = v3_cross(camera->direction, result.right_vector);
	result.aspect_ratio = (float)(img->width - 1) / (float)(img->height - 1); // -1 useful?
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

t_vector3 get_normal(t_shape *shape, t_vector3 point)
{
	t_vector3 normal;

	(void)point;
	if (shape->type == SPHERE)
	{
		normal = v3_normalize(v3_subtract(point, shape->data.sphere.position));
	}
	else if (shape->type == PLANE)
	{
		normal = shape->data.plane.normal;
	}
	else if (shape->type == CYLINDER)
	{
		// implement
	}
	else if (shape->type == TORUS)
	{
		// implement
	}
	return (normal);
}

t_color get_shape_color(t_shape *shape)
{
	if (shape->type == SPHERE)
		return (shape->data.sphere.color);
	else if (shape->type == PLANE)
		return (shape->data.plane.color);
	else if (shape->type == CYLINDER)
		return (shape->data.cylinder.color);
	else if (shape->type == TORUS)
		return (shape->data.torus.color);
	return (t_color){0};
}

// t = intersection distance
// returns 0 if no intersection
// returns 1 if intersection, and fills hit_info if it it not NULL
int get_closest_shape_intersecting(t_ray *ray, t_list *shapes, t_ray_hit_info *hit_info)
{
	t_shape *closest_shape;
	float t;
	float closest_t;

	closest_shape = NULL;
	closest_t = __FLT_MAX__;
	while (shapes)
	{
		t_shape *shape = (t_shape *)shapes->content;
		if (shape->type == SPHERE && intersect_sphere(ray, &shape->data.sphere, &t) && t < closest_t)
		{
 			closest_t = t;
			closest_shape = shape;
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
		else if (shape->type == TORUS)
		{
			// torus check
		}
		shapes = shapes->next;
	}
	if (closest_shape)
	{
		if (hit_info)
		{
			hit_info->position = v3_add(ray->origin, v3_scale(ray->direction, closest_t));
			hit_info->normal = get_normal(closest_shape, hit_info->position);
			hit_info->shape = closest_shape;
		}
		return (1);
	}
	return (0);
}

// precompute lights intensities ?
t_color apply_phong(t_scene *scene, t_ray_hit_info *hit_info)
{
	t_color shape_color;
	t_color final_color;
	t_ray	light_ray;

	shape_color = get_shape_color(hit_info->shape);
	t_color ambiant = color_multiply(shape_color, color_scale(scene->ambiant_light->color, scene->ambiant_light->ratio));
	final_color = ambiant;
	light_ray.origin = hit_info->position;
	t_list *light_list = scene->lights;
	while (light_list)
	{
		t_light *light = light_list->content;
		light_ray.direction = v3_normalize(v3_subtract(light->position, light_ray.origin));
		if (!get_closest_shape_intersecting(&light_ray, scene->shapes, NULL))
		{
			// diffuse
			float diffuse_factor = fmaxf(0, v3_dot(light_ray.direction, hit_info->normal));
			t_color diffuse = color_multiply(shape_color, color_scale(color_scale(light->color, light->brightness), diffuse_factor));
			// specular
			t_color specular = {0};
			// apply attenuation depending on range from light ? (bonus bonus)
			final_color = color_add(final_color, color_add(diffuse, specular));
		}
		light_list = light_list->next;
	}
	return (final_color);
}

t_color trace_ray(t_ray *ray, t_scene *scene)
{
	t_color color;
	t_ray_hit_info hit_info;

	ft_memset(&color, 0, sizeof(t_color));
	if (get_closest_shape_intersecting(ray, scene->shapes, &hit_info))
	{
		color = apply_phong(scene, &hit_info);
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
