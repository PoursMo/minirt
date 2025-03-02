/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:00:26 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/02 21:44:44 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Check for ray collisions with shapes
int	check_ray_collision(t_ray *ray, t_list *shapes, float max_distance)
{
	float	distance;

	while (shapes)
	{
		if (intersect_shape(ray, shapes->content, &distance)
			&& distance < max_distance)
			return (1);
		shapes = shapes->next;
	}
	return (0);
}

// Sample color from an image using UV coordinates
t_color	sample_image(t_vector2 uv, t_img *image)
{
	t_color	color;
	int		x;
	int		y;

	x = (int)(uv.x * image->width) % image->width;
	y = (int)(uv.y * image->height) % image->height;
	color = get_pixel_from_mlx_img(image, x, y);
	return (color);
}

t_color	compute_final_color(t_scene *scene, t_ray_hit_info *hit_info,
	t_color point_color, t_vector3 normal)
{
	t_color		final_color;
	t_ray		light_ray;
	t_list		*light_list;
	t_light		*light;
	t_vector3	dir;

	light_ray.origin = v3_add(hit_info->position,
			v3_scale(hit_info->normal, EPSILON));
	final_color = compute_ambiant(point_color, scene->ambiant_light);
	light_list = scene->lights;
	while (light_list)
	{
		light = light_list->content;
		dir = v3_subtract(light->position, light_ray.origin);
		light_ray.direction = v3_normalize(dir);
		if (!check_ray_collision(&light_ray, scene->shapes,
				v3_get_magnitude(dir)))
		{
			final_color = color_add(final_color, color_add(
						compute_diffuse(point_color, light, &light_ray, normal),
						compute_specular(light, &light_ray, hit_info, normal)));
		}
		light_list = light_list->next;
	}
	return (final_color);
}

float	get_grayscale(t_color c)
{
	float	red;
	float	green;
	float	blue;

	red = (float)c.red / 255;
	green = (float)c.green / 255;
	blue = (float)c.blue / 255;
	return ((red + green + blue) / 3);
}

// precompute lights intensities ?
t_color	apply_phong(t_scene *scene, t_ray_hit_info *hit_info)
{
	t_color		point_color;
	t_vector3	normal;

	point_color = hit_info->shape->color;
	if (hit_info->shape->texture)
		point_color = color_add(point_color, sample_image(compute_shape_uv(hit_info), hit_info->shape->texture));
	normal = hit_info->normal;
	// if (hit_info->shape->bump_map)
	// 	normal = v3_scale(normal, get_grayscale(sample_image(compute_shape_uv(hit_info), hit_info->shape->bump_map)));
	return (compute_final_color(scene, hit_info, point_color, normal));
}
