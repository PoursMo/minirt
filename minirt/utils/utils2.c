/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:56:56 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/06 14:57:03 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Sample color from an image using UV coordinates
t_color	sample_image(t_vector2 uv, t_img *image)
{
	t_color	color;
	int		x;
	int		y;

	x = (int)(uv.x * image->width) % image->width;
	y = (int)(uv.y * image->height) % image->height;
	color = get_pixel_from_mlx_img(image, x, y);
	return (color);
}
