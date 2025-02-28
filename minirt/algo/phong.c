/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:00:26 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:34:02 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	calculate_ambient(t_color *shape_color, t_scene *scene)
{
	return (color_multiply(*shape_color, color_scale(scene->ambiant_light->color, scene->ambiant_light->ratio)));
}

static t_color	calculate_diffuse(t_ray *light_ray, t_ray_hit_info *hit_info, t_color *shape_color, t_light *light)
{
	float	diffuse_factor;

	diffuse_factor = fmaxf(0, v3_dot(light_ray->direction, hit_info->normal));
	return (color_multiply(*shape_color, color_scale(color_scale(light->color, light->brightness), diffuse_factor)));
}

static t_color	calculate_specular(t_ray *light_ray, t_ray_hit_info *hit_info, t_light *light, t_scene *scene)
{
	t_vector3	view_dir;
	t_vector3	reflect_dir;
	float		specular_factor;

	view_dir = v3_normalize(v3_subtract(scene->camera->position, hit_info->position));
	reflect_dir = v3_reflect(v3_negate(light_ray->direction), hit_info->normal);
	specular_factor = powf(fmaxf(v3_dot(view_dir, reflect_dir), 0.0f), 32);
	return (color_scale(light->color, specular_factor * light->brightness));
}

int is_ray_colliding(t_ray *ray, t_list *shapes)
{
	float t;
	t_shape *shape;

	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if ((shape->type == SPHERE && intersect_sphere(ray, &shape->data.sphere, &t))
			|| (shape->type == PLANE && intersect_plane(ray, &shape->data.plane, &t))) // add cylinder and torus
		{
 			return (1);
		}
		shapes = shapes->next;
	}
	return (0);
}

// precompute lights intensities ?
t_color	apply_phong(t_scene *scene, t_ray_hit_info *hit_info)
{
	t_color final_color;
	t_ray	light_ray;

	final_color = calculate_ambient(&hit_info->shape->color, scene);
	light_ray.origin = v3_add(hit_info->position, v3_scale(hit_info->normal, 1e-4));
	t_list *light_list = scene->lights;
	while (light_list)
	{
		t_light *light = light_list->content;
		light_ray.direction = v3_normalize(v3_subtract(light->position, light_ray.origin));
		if (!is_ray_colliding(&light_ray, scene->shapes))
		{
			final_color = color_add(final_color, color_add(calculate_diffuse(&light_ray, hit_info, &hit_info->shape->color, light), calculate_specular(&light_ray, hit_info, light, scene)));
		}
		light_list = light_list->next;
	}
	return (final_color);
}
