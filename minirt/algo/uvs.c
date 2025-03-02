/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:43:56 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/02 18:58:29 by aloubry          ###   ########.fr       */
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

// torus uv

t_vector2	compute_shape_uv(t_ray_hit_info *info)
{
	if (info->shape->type == SPHERE)
		return (compute_sphere_uv(info->normal));
	// else if (info->shape->type == PLANE)
	// 	return (compute_plane_uv(info->normal));
	// else if (info->shape->type == CYLINDER)
	// 	return (compute_cylinder_uv(info->normal));
	// else if (info->shape->type == TORUS)
	// 	return (compute_torus_uv(info->normal));
	return ((t_vector2){0});
}
