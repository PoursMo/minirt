/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:38:32 by lpittet           #+#    #+#             */
/*   Updated: 2025/03/11 10:02:12 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	check_for_caps(t_ray *ray, t_cylinder *cyl, float *intersect_dist)
{
	t_vector3	center2;
	float		dot_normal;
	float		t;
	t_vector3	hit;

	dot_normal = v3_dot(cyl->axis, ray->direction);
	if (fabs(dot_normal) < 1e-9)
		return ;
	center2 = v3_add(cyl->position, v3_scale(cyl->axis, cyl->height));
	t = v3_dot(v3_subtract(cyl->position, ray->origin), cyl->axis) / dot_normal;
	if (t > 0 && (*intersect_dist < 0 || t < *intersect_dist))
	{
		hit = v3_add(ray->origin, v3_scale(ray->direction, t));
		if (v3_get_magnitude(v3_subtract(hit, cyl->position)) < cyl->radius)
			*intersect_dist = t;
	}
	t = v3_dot(v3_subtract(center2, ray->origin), cyl->axis) / dot_normal;
	if (t > 0 && (*intersect_dist < 0 || t < *intersect_dist))
	{
		hit = v3_add(ray->origin, v3_scale(ray->direction, t));
		if (v3_get_magnitude(v3_subtract(hit, center2)) < cyl->radius)
			*intersect_dist = t;
	}
}
