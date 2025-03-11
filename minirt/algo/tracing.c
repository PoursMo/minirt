/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:04:55 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/11 12:48:38 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// returns 3d coordinates of a pixel in our world depending on camera
static t_vector3	pixel_to_world_coordinates(
		t_precomputed_camera *precomputed_camera, int x, int y)
{
	float		u;
	float		v;
	t_vector3	scaled_right;
	t_vector3	scaled_up;
	t_vector3	pixel_world;

	u = (2 * (x + 0.5) / (float)WIDTH - 1)
		* precomputed_camera->viewport_width / 2;
	v = (1 - 2 * (y + 0.5) / (float)HEIGHT)
		* precomputed_camera->viewport_height / 2;
	scaled_right = v3_scale(precomputed_camera->right_vector, u);
	scaled_up = v3_scale(precomputed_camera->up_vector, v);
	pixel_world = v3_add(v3_add(
				v3_add(precomputed_camera->origin, scaled_right),
				scaled_up), precomputed_camera->forward_vector);
	return (pixel_world);
}

// returns ray for pixel x, y with normalized direction
t_ray	get_ray(int x, int y, t_precomputed_camera *precomputed)
{
	t_ray		ray;
	t_vector3	pixel_world;

	ray.origin = precomputed->origin;
	pixel_world = pixel_to_world_coordinates(precomputed, x, y);
	ray.direction = v3_normalize(v3_subtract(pixel_world, precomputed->origin));
	return (ray);
}

// t = intersection distance
// returns 0 if no intersection
// returns 1 if intersection, and fills hit_info if it it not NULL
static int	get_closest_shape_intersecting(t_ray *ray, t_list *shapes,
	t_ray_hit_info *info)
{
	t_shape	*closest_shape;
	float	t;
	float	min_t;

	closest_shape = NULL;
	min_t = __FLT_MAX__;
	while (shapes)
	{
		t = -EPSILON;
		if (intersect_shape(ray, shapes->content, &t) && t < min_t)
		{
			min_t = t;
			closest_shape = shapes->content;
		}
		shapes = shapes->next;
	}
	if (closest_shape)
	{
		info->ray = ray;
		info->position = v3_add(ray->origin, v3_scale(ray->direction, min_t));
		info->normal = get_normal(closest_shape, info->position, ray);
		info->shape = closest_shape;
		return (1);
	}
	return (0);
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	t_color			color;
	t_ray_hit_info	hit_info;

	color = (t_color){0};
	if (get_closest_shape_intersecting(ray, scene->shapes, &hit_info))
	{
		color = apply_phong(scene, &hit_info);
	}
	return (color);
}
