/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:47:37 by lpittet           #+#    #+#             */
/*   Updated: 2025/03/15 13:14:00 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	get_normals(t_cube *cube, t_vector3 *normals)
{
	t_vector3	normal;
	t_vector3	random;

	normal = cube->axis;
	if (fabs(normal.x) < fabs(normal.y))
		random = (t_vector3){1, 0, 0};
	else
		random = (t_vector3){0, 1, 0};
	normals[0] = normal;
	normals[1] = v3_normalize(v3_cross(normal, random));
	normals[2] = v3_normalize(v3_cross(normal, normals[1]));
	normals[3] = v3_scale(normals[0], -1);
	normals[4] = v3_scale(normals[1], -1);
	normals[5] = v3_scale(normals[2], -1);
}

void	get_centers(t_cube *cube, t_vector3 *centers, t_vector3 *normals)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		centers[i] = v3_add(cube->position, v3_scale(normals[i],
					cube->size / 2));
		i++;
	}
}

int	inside_square(t_vector3 hit_point, t_cube *cube, t_vector3 center_face,
	t_vector3 normal)
{
	t_vector3	normals[6];
	int			i;
	t_vector3	u;
	t_vector3	v;
	t_vector3	point_to_center;

	i = 0;
	get_normals(cube, normals);
	while (fabs(normal.x) - fabs(normals[i].x) > EPSILON
		|| fabs(normal.y) - fabs(normals[i].y) > EPSILON
		|| fabs(normal.z) - fabs(normals[i].z) > EPSILON)
		i++;
	u = normals[(i + 1) % 3];
	v = normals[(i + 2) % 3];
	point_to_center = v3_subtract(hit_point, center_face);
	if (fabs(v3_dot(point_to_center, u)) < cube->size / 2
		&& fabs(v3_dot(point_to_center, v)) < cube->size / 2)
		return (1);
	return (0);
}

void	check_side(t_ray *ray, t_vector3 center_face, t_cube *cube,
	float *intersect_dist)
{
	t_vector3	hit_point;
	float		dist;
	float		denom;
	t_vector3	p0l0;
	t_vector3	normal;

	normal = v3_normalize(v3_subtract(center_face, cube->position));
	denom = v3_dot(ray->direction, normal);
	if (fabs(denom) < EPSILON)
		return ;
	p0l0 = v3_subtract(center_face, ray->origin);
	dist = v3_dot(p0l0, normal) / denom;
	hit_point = v3_add(ray->origin, v3_scale(ray->direction, dist));
	if (dist > 0 && inside_square(hit_point, cube, center_face, normal))
	{
		if (*intersect_dist < 0 || dist < *intersect_dist)
			*intersect_dist = dist;
	}
}
