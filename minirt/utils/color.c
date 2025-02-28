/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:49:24 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:22:28 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_multiply(t_color a, t_color b)
{
	t_color	result;

	result.red = (unsigned char)fminf(a.red * (b.red / 255.0f), 255.0f);
	result.green = (unsigned char)fminf(a.green * (b.green / 255.0f), 255.0f);
	result.blue = (unsigned char)fminf(a.blue * (b.blue / 255.0f), 255.0f);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.red = (unsigned char)fminf(a.red + b.red, 255.0f);
	result.green = (unsigned char)fminf(a.green + b.green, 255.0f);
	result.blue = (unsigned char)fminf(a.blue + b.blue, 255.0f);
	return (result);
}

t_color	color_scale(t_color c, float scalar)
{
	t_color	result;

	result.red = c.red * scalar;
	result.green = c.green * scalar;
	result.blue = c.blue * scalar;
	return (result);
}
