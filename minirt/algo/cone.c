/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:41:45 by lpittet           #+#    #+#             */
/*   Updated: 2025/03/14 09:17:48 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_for_cone_len(t_cone *cone, t_ray *ray, float t[2],
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
	t_vector3	base_hit;

	denom = v3_dot(cone->axis, ray->direction);
	if (fabs(denom) < EPSILON)
		return ;
	p0l0 = v3_subtract(cone->position, ray->origin);
	dist = v3_dot(p0l0, cone->axis) / denom;
	if (dist < 0 || dist > *intersect_dist)
		return ;
	hit_point = v3_add(ray->origin, v3_scale(ray->direction, dist));
	base_hit = v3_subtract(hit_point, cone->position);
	if (v3_dot(base_hit, base_hit) < cone->radius * cone->radius)
	{
		*intersect_dist = dist;
		cone->hit_pos = BASE;
	}
}

int	check_inside_cone(t_cone *cone, t_vector3 cam_proj, float dist_cam_axis)
{
	float		local_radius;

	local_radius = tan(cone->angle) * (cone->height
			- v3_get_magnitude(v3_subtract(cam_proj, cone->position)));
	if (dist_cam_axis >= local_radius)
		return (0);
	return (v3_get_magnitude(v3_subtract(cam_proj,
				cone->position)) < cone->height);
}
