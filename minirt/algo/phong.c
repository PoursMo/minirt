/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:00:26 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/08 12:43:26 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Check for ray collisions with shapes
int	check_ray_collision(t_ray *ray, t_list *shapes, float max_distance)
{
	float	distance;

	while (shapes)
	{
		distance = -EPSILON;
		if (intersect_shape(ray, shapes->content, &distance)
			&& distance < max_distance)
			return (1);
		shapes = shapes->next;
	}
	return (0);
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

t_color	apply_phong(t_scene *scene, t_ray_hit_info *hit_info)
{
	t_color		point_color;
	t_vector3	normal;
	t_vector2	uvs;

	if (hit_info->shape->bump_map || hit_info->shape->texture)
		uvs = compute_shape_uv(hit_info);
	point_color = hit_info->shape->color;
	if (hit_info->shape->texture && uvs.x != -1 && uvs.y != -1)
		point_color = color_add(point_color, sample_image(uvs, hit_info->shape->texture));
	normal = hit_info->normal;
	if (hit_info->shape->bump_map && uvs.x != -1 && uvs.y != -1)
		normal = perturb_normal(uvs, hit_info);
	return (compute_final_color(scene, hit_info, point_color, normal));
}
