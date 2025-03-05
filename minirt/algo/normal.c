/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:39:42 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/05 08:31:45 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector3	cylinder_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3	plane_hit_axis;
	t_vector3	normal;

	if (v3_get_magnitude(v3_subtract(shape->data.cylinder.position, point))
		< shape->data.cylinder.radius
		|| v3_get_magnitude(v3_subtract(v3_add(shape->data.cylinder.position,
					v3_scale(shape->data.cylinder.axis,
						shape->data.cylinder.height)), point))
		< shape->data.cylinder.radius)
	{
		if (v3_dot(ray->direction, shape->data.cylinder.axis) >= 0)
			return (v3_scale(shape->data.cylinder.axis, -1));
		return (shape->data.cylinder.axis);
	}
	plane_hit_axis = v3_cross(shape->data.cylinder.axis,
			v3_subtract(point, shape->data.cylinder.position));
	normal = v3_cross(plane_hit_axis, shape->data.cylinder.axis);
	return (v3_normalize(normal));
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
		normal = cylinder_normal(shape, point, ray);
	else if (shape->type == CONE)
	{
		normal = shape->data.cone.axis;
	}
	return (normal);
}
