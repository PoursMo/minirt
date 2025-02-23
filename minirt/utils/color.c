/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:49:24 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/23 15:38:33 by aloubry          ###   ########.fr       */
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

int	color_to_int(t_color color)
{
	return (rgb_to_int(color.red, color.green, color.blue));
}

void	place_pixel_in_mlx_img(t_img *img, int x, int y, t_color color)
{
	int	pixel;

	pixel = (y * img->size_line) + (x * (img->bpp / 8));
	if (img->image->byte_order == 0)
	{
		img->data[pixel + 0] = color.blue;
		img->data[pixel + 1] = color.green;
		img->data[pixel + 2] = color.red;
		img->data[pixel + 3] = 0x00;
	}
	else
	{
		img->data[pixel + 0] = 0x00;
		img->data[pixel + 1] = color.red;
		img->data[pixel + 2] = color.green;
		img->data[pixel + 3] = color.blue;
	}
}
