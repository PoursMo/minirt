/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:44:39 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 11:39:47 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v3_get_magnitude(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	v3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	v3_up(void)
{
	return ((t_vector3){0, -1, 0});
}

t_vector3	v3_reflect(t_vector3 v, t_vector3 normal)
{
    return (v3_subtract(v, v3_scale(normal, 2 * v3_dot(v, normal))));
}
