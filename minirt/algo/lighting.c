/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:41:17 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 15:35:30 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_ambiant(t_color base_color, t_ambiant_light *ambiant_light)
{
	return (color_multiply(base_color, ambiant_light->scaled_color));
}

t_color	compute_diffuse(t_color base_color, t_light *light,
		t_ray *light_ray, t_vector3 normal)
{
	float	diffuse_factor;
	t_color	diffused_light;

	diffuse_factor = fmaxf(0, v3_dot(light_ray->direction, normal));
	diffused_light = color_scale(light->scaled_color, diffuse_factor);
	return (color_multiply(base_color, diffused_light));
}

t_color	compute_specular(t_light *light, t_ray *light_ray,
		t_ray_hit_info *hit_info, t_vector3 normal)
{
	t_vector3	view_dir;
	t_vector3	reflect_dir;
	float		specular_factor;

	view_dir = v3_scale(hit_info->ray->direction, -1);
	reflect_dir = v3_reflect(v3_scale(light_ray->direction, -1), normal);
	specular_factor = powf(fmaxf(0, v3_dot(view_dir, reflect_dir)), SHININESS);
	return (color_scale(light->color, specular_factor * light->brightness));
}
