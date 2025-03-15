/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:51:30 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/15 14:16:18 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_grayscale(t_color c)
{
	float	red;
	float	green;
	float	blue;

	red = (float)c.red / 255;
	green = (float)c.green / 255;
	blue = (float)c.blue / 255;
	return ((red + green + blue) / 3);
}

static float	compute_values(t_vector2 uvs, t_img *bump_map,
	float *dhdu, float *dhdv)
{
	float	bump_value;

	bump_value = get_grayscale(sample_image(uvs, bump_map));
	*dhdu = get_grayscale(sample_image(
				(t_vector2){1.0 / bump_map->width + uvs.x, uvs.y},
				bump_map)) - bump_value;
	*dhdv = get_grayscale(sample_image(
				(t_vector2){uvs.x, 1.0 / bump_map->height + uvs.y},
				bump_map)) - bump_value;
	return (bump_value);
}

t_vector3	perturb_normal(t_vector2 uvs, t_ray_hit_info *hit_info)
{
	float		bump_value;
	float		dhdu;
	float		dhdv;
	t_vector3	tangent;
	t_vector3	bitangent;

	bump_value = compute_values(uvs, hit_info->shape->bump_map, &dhdu, &dhdv);
	if (fabs(hit_info->normal.y) > 0.99999)
		tangent = v3_cross(hit_info->normal, (t_vector3){1.0, 0.0, 0.0});
	else
		tangent = v3_cross(hit_info->normal, (t_vector3){0.0, 1.0, 0.0});
	bitangent = v3_cross(hit_info->normal, tangent);
	return (v3_normalize(v3_add(v3_add(v3_scale(tangent, dhdu),
					v3_scale(bitangent, dhdv)),
				v3_scale(hit_info->normal, bump_value))));
}
