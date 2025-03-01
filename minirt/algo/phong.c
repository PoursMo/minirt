/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:00:26 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/01 21:55:47 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	compute_ambiant_lighting(t_color *shape_color, t_scene *scene)
{
	return (color_multiply(*shape_color, color_scale(scene->ambiant_light->color, scene->ambiant_light->ratio)));
}

static t_color	compute_diffuse_lighting(t_ray *light_ray, t_vector3 normal, t_color *shape_color, t_light *light)
{
	float	diffuse_factor;

	diffuse_factor = fmaxf(0, v3_dot(light_ray->direction, normal));
	return (color_multiply(*shape_color, color_scale(color_scale(light->color, light->brightness), diffuse_factor)));
}

static t_color	compute_specular_lighting(t_ray *light_ray, t_ray_hit_info *hit_info, t_vector3 normal, t_light *light, t_scene *scene)
{
	t_vector3	view_dir;
	t_vector3	reflect_dir;
	float		specular_factor;

	view_dir = v3_normalize(v3_subtract(scene->camera->position, hit_info->position));
	reflect_dir = v3_reflect(v3_negate(light_ray->direction), normal);
	specular_factor = powf(fmaxf(v3_dot(view_dir, reflect_dir), 0.0f), SHININESS);
	return (color_scale(light->color, specular_factor * light->brightness));
}

int check_ray_collision(t_ray *ray, t_list *shapes, float max_distance)
{
	float t;
	
	while (shapes)
	{
		if (intersect_shape(ray, shapes->content, &t) && t < max_distance)
			return (1);
		shapes = shapes->next;
	}
	return (0);
}

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

// precompute lights intensities ?
t_color	apply_phong(t_scene *scene, t_ray_hit_info *hit_info)
{
	t_color		final_color;
	t_ray		light_ray;
	t_color		point_color;
	t_vector3	normal;

	point_color = hit_info->shape->color;
	if (hit_info->shape->texture)
		point_color = color_add(point_color, sample_image(compute_shape_uv(hit_info), hit_info->shape->texture));
	final_color = compute_ambiant_lighting(&point_color, scene);
	light_ray.origin = v3_add(hit_info->position, v3_scale(hit_info->normal, EPSILON));
	normal = hit_info->normal;
	// if (hit_info->shape->bump_map)
	// 	normal = apply bump map;
	t_list *light_list = scene->lights;
	while (light_list)
	{
		t_light *light = light_list->content;
		t_vector3 dir = v3_subtract(light->position, light_ray.origin);
		light_ray.direction = v3_normalize(dir);
		if (!check_ray_collision(&light_ray, scene->shapes, v3_get_magnitude(dir)))
		{
			final_color = color_add(final_color, color_add(compute_diffuse_lighting(&light_ray, normal, &point_color, light), compute_specular_lighting(&light_ray, hit_info, normal, light, scene)));
		}
		light_list = light_list->next;
	}
	return (final_color);
}
