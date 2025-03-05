/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:43:56 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/04 19:20:31 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector2	compute_plane_uv(t_vector3 position, t_vector3 normal)
{
	t_vector3 u_axis = (fabs(normal.y) > 0.9) ? (t_vector3){1, 0, 0} : (t_vector3){0, 1, 0};
	t_vector3 v_axis = v3_cross(normal, u_axis);
	u_axis = v3_cross(v_axis, normal);

	float u = v3_dot(position, u_axis) - floor(v3_dot(position, u_axis));
	float v = v3_dot(position, v_axis) - floor(v3_dot(position, v_axis));
	return (t_vector2){u, v};
}

static t_vector2	compute_sphere_uv(t_vector3 normal)
{
	float u = 0.5 + atan2(normal.z, normal.x) / (2 * MRT_PI);
	float v = 0.5 - asin(normal.y) / MRT_PI;
	return (t_vector2){u, v};
}

static t_vector2	compute_cylinder_uv(t_vector3 position, t_vector3 normal, t_vector3 axis)
{
	t_vector3 u_axis = v3_cross(axis, (fabs(axis.y) > 0.9) ? (t_vector3){1, 0, 0} : (t_vector3){0, 1, 0});
	t_vector3 v_axis = v3_cross(axis, u_axis);

	float theta = atan2(v3_dot(normal, v_axis), v3_dot(normal, u_axis));
	float u = (theta + MRT_PI) / (2 * MRT_PI);
	float v = v3_dot(position, axis) - floor(v3_dot(position, axis));
	return (t_vector2){u, v};
}

// cone

t_vector2	compute_shape_uv(t_ray_hit_info *info)
{
	if (info->shape->type == SPHERE)
		return (compute_sphere_uv(info->normal));
	else if (info->shape->type == PLANE)
		return (compute_plane_uv(info->position, info->normal));
	else if (info->shape->type == CYLINDER)
		return (compute_cylinder_uv(info->position, info->normal, info->shape->data.cylinder.axis));
	// else if (info->shape->type == CONE)
	// 	return (compute_cone_uv(info->normal));
	return ((t_vector2){0});
}
