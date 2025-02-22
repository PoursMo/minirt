/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:49:24 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/22 16:13:43 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_int(unsigned char red, unsigned char green, unsigned char blue)
{
	int	color;

	color = red << 16;
	color += green << 8;
	color += blue;
	return (color);
}

int	t_color_to_int(t_color color)
{
	return (rgb_to_int(color.red, color.green, color.blue));
}
