/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:44:39 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 23:34:17 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	v3_get_magnitude(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	v3_dot(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3	v3_up(void)
{
	return ((t_vector3){.x = 0, .y = 1, .z = 0});
}