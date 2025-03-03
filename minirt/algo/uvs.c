/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:43:56 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 14:13:38 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector2	compute_sphere_uv(t_vector3 normal)
{
	float	theta = acos(normal.y);
	float	phi = atan2(normal.z, normal.x);

	float u = (phi + MRT_PI) / (2.0 * MRT_PI);
	float v = theta / MRT_PI;
	return (t_vector2){u, v};
}

// plane uv

// cylinder uv

// cone uv

t_vector2	compute_shape_uv(t_ray_hit_info *info)
{
	if (info->shape->type == SPHERE)
		return (compute_sphere_uv(info->normal));
	// else if (info->shape->type == PLANE)
	// 	return (compute_plane_uv(info->normal));
	// else if (info->shape->type == CYLINDER)
	// 	return (compute_cylinder_uv(info->normal));
	// else if (info->shape->type == CONE)
	// 	return (compute_cone_uv(info->normal));
	return ((t_vector2){0});
}
