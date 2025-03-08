/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/07 15:11:36 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist)
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

static int intersect_sphere(t_ray *ray, t_sphere *sphere, float *intersect_dist)
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
			if (*intersect_dist < 0 || t[1] < *intersect_dist)
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
	if (t > 0 && (*intersect_dist < 0 || t < *intersect_dist))
	{
		hit = v3_add(ray->origin, v3_scale(ray->direction, t));
		if (v3_get_magnitude(v3_subtract(hit, cylinder->position)) <= cylinder->radius)
			*intersect_dist = t;
	}
	t = v3_dot(v3_subtract(center2, ray->origin), cylinder->axis) / dot_normal;
	if (t > 0 && (*intersect_dist < 0 || t < *intersect_dist))
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
	if (*intersect_dist < 0)
		return (0);
	return (1);
}

void	check_for_cone_len(t_cone *cone, t_ray *ray, float	t[2],
	float *intersect_dist)
{
	float		p;
	t_vector3	hit_point;
	t_vector3	apex;

	apex = v3_add(cone->position, v3_scale(cone->axis, cone->height));
	if (t[0] > 0)
	{
		hit_point = v3_add(ray->origin, v3_scale(ray->direction, t[0]));
		p = v3_dot(v3_subtract(hit_point, apex), v3_scale(cone->axis, -1));
		if (p >= 0 && p <= cone->height)
			*intersect_dist = t[0];
	}
	if (t[1] > 0)
	{
		hit_point = v3_add(ray->origin, v3_scale(ray->direction, t[1]));
		p = v3_dot(v3_subtract(hit_point, apex), v3_scale(cone->axis, -1));
		if (p >= 0 && p <= cone->height)
		{
			if (*intersect_dist < 0 || t[1] < *intersect_dist)
				*intersect_dist = t[1];
		}
	}
}

void	check_for_cone_base(t_cone *cone, t_ray *ray, float *intersect_dist)
{
	t_vector3	hit_point;
	float		dist;
	float		denom;
	t_vector3	p0l0;
	
	denom = v3_dot(cone->axis, ray->direction);
	if (fabs(denom) > 1e-6)
		return ;
	p0l0 = v3_subtract(cone->position, ray->origin);
	dist = v3_dot(p0l0, cone->axis) / denom;
	hit_point = v3_scale(ray->direction, dist);
	if (v3_get_magnitude(v3_subtract(hit_point, cone->position)) <= cone->radius
		&& dist < *intersect_dist)
		*intersect_dist = dist;
}

int	intersect_cone(t_ray *ray, t_cone *cone, float *intersect_dist)
{
	float		quad[4];
	float		t[2];
	t_vector3	cam_obj;
	
	cam_obj = v3_subtract(ray->origin, cone->position);
	quad[0] = pow(v3_dot(ray->direction, cone->axis),2) - pow(cos(cone->angle), 2);
	quad[1] = 2 * ((v3_dot(ray->direction, cone->axis)) * v3_dot(cam_obj, cone->axis)
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
	return (0);
}
