/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:44:39 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/26 15:17:05 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	v3_cross(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector3	v3_scale(t_vector3 v, float scalar)
{
	t_vector3	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_vector3	v3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	v3_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	v3_normalize(t_vector3 v)
{
	float		magnitude;
	t_vector3	normalized_vector;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (magnitude == 0)
	{
		normalized_vector.x = 0;
		normalized_vector.y = 0;
		normalized_vector.z = 0;
	}
	else
	{
		normalized_vector.x = v.x / magnitude;
		normalized_vector.y = v.y / magnitude;
		normalized_vector.z = v.z / magnitude;
	}
	return (normalized_vector);
}
