/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/14 14:00:23 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist)
{
	float		denom;
	t_vector3	p0l0;

	denom = v3_dot(plane->normal, ray->direction);
	if (fabs(denom) > 1e-6)
	{
		p0l0 = v3_subtract(plane->position, ray->origin);
		*intersect_dist = v3_dot(p0l0, plane->normal) / denom;
		return (*intersect_dist >= 0);
	}
	return (0);
}

static int	intersect_sphere(t_ray *ray, t_sphere *sphere,
	float *intersect_dist)
{
	float		discriminant;
	float		ans1;
	float		ans2;
	t_vector3	dist;

	dist = v3_subtract(ray->origin, sphere->position);
	discriminant = v3_dot(ray->direction, dist) * v3_dot(ray->direction, dist)
		- (v3_get_magnitude(dist)
			* v3_get_magnitude(dist) - sphere->radius * sphere->radius);
	if (discriminant < 0)
		return (0);
	ans1 = -(v3_dot(ray->direction, dist)) + sqrt(discriminant);
	ans2 = -(v3_dot(ray->direction, dist)) - sqrt(discriminant);
	if (ans2 < 0 && ans1 < 0)
		return (0);
	else if (ans1 < 0)
		*intersect_dist = ans2;
	else if (ans2 < 0)
		*intersect_dist = ans1;
	else
		*intersect_dist = fminf(ans1, ans2);
	return (1);
}

int	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *intersect_dist)
{
	float		quad[4];
	float		t[2];
	t_vector3	cam_obj;

	cam_obj = v3_subtract(ray->origin, cylinder->position);
	quad[0] = 1 - v3_dot(ray->direction, cylinder->axis)
		* v3_dot(ray->direction, cylinder->axis);
	quad[1] = 2 * (v3_dot(ray->direction, cam_obj)
			- v3_dot(ray->direction, cylinder->axis)
			* v3_dot(cam_obj, cylinder->axis));
	quad[2] = v3_dot(cam_obj, cam_obj) - v3_dot(cam_obj, cylinder->axis)
		* v3_dot(cam_obj, cylinder->axis) - cylinder->radius * cylinder->radius;
	quad[3] = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (quad[3] < 0)
		return (0);
	t[0] = (-quad[1] - sqrtf(quad[3])) / (2 * quad[0]);
	t[1] = (-quad[1] + sqrtf(quad[3])) / (2 * quad[0]);
	check_for_cylinder_len(cylinder, ray, t, intersect_dist);
	check_for_caps(ray, cylinder, intersect_dist);
	if (*intersect_dist < 0)
		return (0);
	return (1);
}

int	intersect_cone(t_ray *ray, t_cone *cone, float *intersect_dist)
{
	float		quad[4];
	float		t[2];
	t_vector3	cam_obj;

	cam_obj = v3_subtract(ray->origin, cone->position);
	quad[0] = pow(v3_dot(ray->direction, cone->axis), 2)
		- pow(cos(cone->angle), 2);
	quad[1] = 2 * ((v3_dot(ray->direction, cone->axis))
			* v3_dot(cam_obj, cone->axis)
			- v3_dot(ray->direction, cam_obj) * pow(cos(cone->angle), 2));
	quad[2] = pow(v3_dot(cam_obj, cone->axis), 2)
		- pow(v3_get_magnitude(cam_obj), 2) * pow(cos(cone->angle), 2);
	quad[3] = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (quad[3] < 0)
		return (0);
	t[0] = (-quad[1] - sqrt(quad[3])) / (2 * quad[0]);
	t[1] = (-quad[1] + sqrt(quad[3])) / (2 * quad[0]);
	check_for_cone_len(cone, ray, t, intersect_dist);
	check_for_cone_base(cone, ray, intersect_dist);
	if (*intersect_dist < 0)
		return (0);
	return (1);
}

int	intersect_shape(t_ray *ray, t_shape *shape, float *t)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(ray, &shape->data.sphere, t));
	else if (shape->type == PLANE)
		return (intersect_plane(ray, &shape->data.plane, t));
	else if (shape->type == CYLINDER)
		return (intersect_cylinder(ray, &shape->data.cylinder, t));
	else if (shape->type == CONE)
		return (intersect_cone(ray, &shape->data.cone, t));
	else if (shape->type == CUBE)
		return (intersect_cube(ray, &shape->data.cone, t));
	return (0);
}
