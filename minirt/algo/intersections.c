/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 18:09:11 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist)
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
