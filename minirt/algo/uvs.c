/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:43:56 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/14 14:01:25 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector2	compute_plane_uv(t_vector3 position, t_vector3 normal)
{
	t_vector3	u_axis;
	t_vector3	v_axis;
	float		u;
	float		v;

	if (fabs(normal.y) > 0.9999)
		u_axis = v3_cross((t_vector3){1, 0, 0}, normal);
	else
		u_axis = v3_cross((t_vector3){0, 1, 0}, normal);
	v_axis = v3_cross(normal, u_axis);
	u = v3_dot(position, u_axis) - floor(v3_dot(position, u_axis));
	v = v3_dot(position, v_axis) - floor(v3_dot(position, v_axis));
	return ((t_vector2){u, v});
}

static t_vector2	compute_sphere_uv(t_vector3 normal)
{
	float	u;
	float	v;

	u = 0.5 + atan2(normal.z, normal.x) / (2 * MRT_PI);
	v = 0.5 + asin(normal.y) / MRT_PI;
	return ((t_vector2){u, v});
}

static t_vector2	compute_cylinder_uv(t_vector3 position,
	t_vector3 normal, t_vector3 axis)
{
	t_vector3	u_axis;
	t_vector3	v_axis;
	float		u;
	float		v;
	float		theta;

	if (fabs(axis.y) > 0.9999)
		u_axis = v3_cross((t_vector3){1, 0, 0}, axis);
	else
		u_axis = v3_cross((t_vector3){0, 1, 0}, axis);
	v_axis = v3_cross(axis, u_axis);
	theta = atan2(v3_dot(normal, v_axis), v3_dot(normal, u_axis));
	u = (theta + MRT_PI) / (2 * MRT_PI);
	v = v3_dot(position, axis) - floor(v3_dot(position, axis));
	return ((t_vector2){u, v});
}

static t_vector3	compute_cone_apex(t_cone *cone)
{
	return (v3_subtract(cone->position, v3_scale(cone->axis, cone->height)));
}

static t_vector2	compute_cone_uv(t_vector3 position, t_vector3 normal, t_vector3 apex, t_vector3 axis, float height)
{
	t_vector3	u_axis;
	t_vector3	v_axis;
	float		u;
	float		v;
	float		theta;
	float		distance;

	if (fabs(axis.y) > 0.9999)
		u_axis = v3_cross((t_vector3){1, 0, 0}, axis);
	else
		u_axis = v3_cross((t_vector3){0, 1, 0}, axis);
	v_axis = v3_cross(axis, u_axis);
	theta = atan2(v3_dot(normal, v_axis), v3_dot(normal, u_axis));
	u = (theta + MRT_PI) / (2 * MRT_PI);
	distance = v3_get_magnitude(v3_subtract(position, apex));
	v = distance / height - floor(distance / height);
	return ((t_vector2){u, v});
}

t_vector2	compute_shape_uv(t_ray_hit_info *info)
{
	t_cylinder	*cylinder;
	t_cone		*cone;

	if (info->shape->type == SPHERE)
		return (compute_sphere_uv(info->normal));
	else if (info->shape->type == PLANE || info->shape->type == CUBE)
		return (compute_plane_uv(info->position, info->normal));
	else if (info->shape->type == CYLINDER)
	{
		cylinder = &info->shape->data.cylinder;
		if (fabsf(v3_dot(info->normal, cylinder->axis)) > 0.9999)
			return (compute_plane_uv(info->position, info->normal));
		return (compute_cylinder_uv(info->position,
				info->normal, cylinder->axis));
	}
	else if (info->shape->type == CONE)
	{
		cone = &info->shape->data.cone;
		if (v3_dot(info->normal, cone->axis) > 0.9999)
			return (compute_plane_uv(info->position, info->normal));
		return (compute_cone_uv(info->position, info->normal,
				compute_cone_apex(cone), cone->axis, cone->height));
	}
	return ((t_vector2){-1, -1});
}
