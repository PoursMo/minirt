/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:39:42 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/11 12:50:33 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	proj_on_axis(t_shape *shape, t_vector3 point)
{
	t_vector3	pos_point;
	t_vector3	position;
	t_vector3	axis;

	if (shape->type == CYLINDER)
	{
		position = shape->data.cylinder.position;
		axis = shape->data.cylinder.axis;
		pos_point = v3_subtract(point, position);
	}
	if (shape->type == CONE)
	{
		position = shape->data.cone.position;
		axis = shape->data.cone.axis;
		pos_point = v3_subtract(point, position);
	}
	return (v3_add(position, v3_scale(axis, v3_dot(pos_point, axis))));
}

static int	check_inside(t_shape *shape, t_vector3 cam_pos)
{
	t_vector3	cam_proj;
	float		dist_cam_axis;

	if (shape->type == SPHERE)
		return (v3_get_magnitude(v3_subtract(cam_pos,
					shape->data.sphere.position)) < shape->data.sphere.radius);
	if (shape->type == PLANE)
		return (0);
	cam_proj = proj_on_axis(shape, cam_pos);
	dist_cam_axis = v3_get_magnitude(v3_subtract(cam_pos, cam_proj));
	if (shape->type == CYLINDER)
	{
		if (dist_cam_axis >= shape->data.cylinder.radius)
			return (0);
		return (v3_get_magnitude(v3_subtract(cam_proj,
					shape->data.cylinder.position))
			< shape->data.cylinder.height);
	}
	if (shape->type == CONE)
	{
		return (check_inside_cone(&shape->data.cone, cam_proj, dist_cam_axis));
	}
	return (0);
}

static t_vector3	cylinder_normal(t_shape *shape, t_vector3 point)
{
	t_vector3	plane_hit_axis;
	t_vector3	normal;

	if (v3_get_magnitude(v3_subtract(shape->data.cylinder.position, point))
		< shape->data.cylinder.radius)
		return (v3_scale(shape->data.cylinder.axis, -1));
	if (v3_get_magnitude(v3_subtract(v3_add(shape->data.cylinder.position,
					v3_scale(shape->data.cylinder.axis,
						shape->data.cylinder.height)), point))
		< shape->data.cylinder.radius)
		return (shape->data.cylinder.axis);
	plane_hit_axis = v3_cross(shape->data.cylinder.axis,
			v3_subtract(point, shape->data.cylinder.position));
	normal = v3_cross(plane_hit_axis, shape->data.cylinder.axis);
	return (v3_normalize(normal));
}

static t_vector3	cone_normal(t_shape *shape, t_vector3 point)
{
	t_vector3	normal;
	t_vector3	apex;
	t_vector3	point_to_apex;
	t_vector3	axis_component;
	float		dot_hit;

	dot_hit = v3_dot(v3_subtract(shape->data.cone.position, point),
			shape->data.cone.axis);
	if (fabs(dot_hit) < EPSILON)
		return (v3_scale(shape->data.cone.axis, -1));
	apex = v3_add(shape->data.cone.position,
			v3_scale(shape->data.cone.axis, shape->data.cone.height));
	point_to_apex = v3_subtract(apex, point);
	if (v3_get_magnitude(v3_subtract(apex, point_to_apex)) < EPSILON)
		return (shape->data.cone.axis);
	axis_component = v3_scale(shape->data.cone.axis,
			v3_dot(point_to_apex, shape->data.cone.axis));
	normal = v3_subtract(point_to_apex, axis_component);
	return (v3_scale(v3_normalize(normal), -1));
}

t_vector3	get_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3	normal;

	if (shape->type == SPHERE)
		normal = v3_normalize(v3_subtract(point, shape->data.sphere.position));
	else if (shape->type == PLANE)
	{
		normal = shape->data.plane.normal;
		if (v3_dot(normal, ray->direction) > 0)
			normal = v3_scale(normal, -1);
	}
	else if (shape->type == CYLINDER)
		normal = cylinder_normal(shape, point);
	else if (shape->type == CONE)
	{
		normal = cone_normal(shape, point);
	}
	if (check_inside(shape, ray->origin))
		normal = v3_scale(normal, -1);
	return (normal);
}
