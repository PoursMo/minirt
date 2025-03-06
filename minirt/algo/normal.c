/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:39:42 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/06 11:01:53 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector3	cylinder_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3	plane_hit_axis;
	t_vector3	normal;
	
	(void)ray;
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

static t_vector3 cone_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3	normal;
	t_vector3	proj_vector;
	t_vector3 	apex;
	t_vector3	perp_vector;
	(void)ray;
	apex = v3_add(shape->data.cone.position,
			v3_scale(shape->data.cone.axis, shape->data.cone.height));
	proj_vector = v3_scale(shape->data.cone.axis,
			v3_dot(v3_subtract(point, apex), shape->data.cone.axis));
	perp_vector = v3_subtract(v3_subtract(point, apex), proj_vector);
	normal = v3_add(v3_scale(shape->data.cone.axis,
		cos(shape->data.cone.angle)),
		v3_scale(v3_normalize(perp_vector), sin(shape->data.cone.angle)));
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
		normal = cone_normal(shape, point, ray);
	}
	// TODO 
	return (normal);
}
