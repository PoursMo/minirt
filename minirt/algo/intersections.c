/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 16:16:06 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist)
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

int	intersect_sphere(t_ray *ray, t_sphere *sphere, float *intersect_dist)
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

void	check_for_cylinder_len(t_cylinder *cylinder, t_ray *ray, float t[2],
	float *intersect_dist)
{
	float		p;
	t_vector3	hit_point;

	if (t[0] > 0)
	{
		hit_point = v3_add(ray->origin, v3_scale(ray->direction, t[0]));
		p = v3_dot(v3_subtract(hit_point, cylinder->position), cylinder->axis);
		if (p >= 0 && p <= cylinder->height)
			*intersect_dist = t[0];
	}
	if (t[1] > 0)
	{
		hit_point = v3_add(ray->origin, v3_scale(ray->direction, t[1]));
		p = v3_dot(v3_subtract(hit_point, cylinder->position), cylinder->axis);
		if (p >= 0 && p <= cylinder->height)
		{
			if (!intersect_dist || t[1] < *intersect_dist)
				*intersect_dist = t[1];
		}
	}
}

void	check_for_caps(t_ray *ray, t_cylinder *cylinder, float *intersect_dist)
{
	t_vector3	center2;
	float		dot_normal;
	float		t;
	t_vector3	hit;

	dot_normal = v3_dot(cylinder->axis, ray->direction);
	if (dot_normal < 1e-6 && dot_normal > -1e-6)
		return ;
	center2 = v3_add(cylinder->position, v3_scale(cylinder->axis, cylinder->height));
	t = v3_dot(v3_subtract(cylinder->position, ray->origin), cylinder->axis) / dot_normal;
	if (t > 0 && (!intersect_dist || t < *intersect_dist))
	{
		hit = v3_add(ray->origin, v3_scale(ray->direction, t));
		if (v3_get_magnitude(v3_subtract(hit, cylinder->position)) <= cylinder->radius)
			*intersect_dist = t;
	}
	t = v3_dot(v3_subtract(center2, ray->origin), cylinder->axis) / dot_normal;
	if (t > 0 && (!intersect_dist || t < *intersect_dist))
	{
		hit = v3_add(ray->origin, v3_scale(ray->direction, t));
		if (v3_get_magnitude(v3_subtract(hit, center2)) <= cylinder->radius)
			*intersect_dist = t;
	}
}

int	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, float *intersect_dist)
{
	float		quad[4];
	float		t[2];
	t_vector3	cam_obj;

	cam_obj = v3_subtract(ray->origin, cylinder->position);
	quad[0] = 1 - v3_dot(ray->direction, cylinder->axis) * v3_dot(ray->direction, cylinder->axis);
	quad[1] = 2 * (v3_dot(ray->direction, cam_obj) - v3_dot(ray->direction, cylinder->axis) * v3_dot(cam_obj, cylinder->axis));
	quad[2] = v3_dot(cam_obj, cam_obj) - v3_dot(cam_obj, cylinder->axis) * v3_dot(cam_obj, cylinder->axis) - cylinder->radius * cylinder->radius;
	quad[3] = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (quad[3] < 0)
		return (0);
	t[0] = (-quad[1] - sqrtf(quad[3])) / (2 * quad[0]);
	t[1] = (-quad[1] + sqrtf(quad[3])) / (2 * quad[0]);
	check_for_cylinder_len(cylinder, ray, t, intersect_dist);
	check_for_caps(ray, cylinder, intersect_dist);
	if (!intersect_dist)
		return (0);
	return (1);
}
