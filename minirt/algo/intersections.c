/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 14:13:23 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist)
{
    float denom;
	t_vector3 p0l0;
	
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
	float discriminant;
	float ans1;
	float ans2;
	t_vector3 dist;

	dist = v3_subtract(ray->origin, sphere->position);
	discriminant = v3_dot(ray->direction, dist) * v3_dot(ray->direction, dist)
					- (v3_get_magnitude(dist) * v3_get_magnitude(dist) - sphere->radius * sphere->radius);
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

//cylinder

//cone

int	intersect_shape(t_ray *ray, t_shape *shape, float *t)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(ray, &shape->data.sphere, t));
	else if (shape->type == PLANE)
		return (intersect_plane(ray, &shape->data.plane, t));
	// else if (shape->type == CYLINDER)
	// 	return (intersect_cylinder(ray, &shape->data.cylinder, t));
	// else if (shape->type == CONE)
	// 	return (intersect_cone(ray, &shape->data.cone, t));
	return (0);
}
