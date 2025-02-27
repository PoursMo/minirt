/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:36:33 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/27 21:59:52 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_loading_screen(t_mrt_data *data)
{
	int		img_w;
	int		img_h;
	t_img	*img;

	img = mlx_xpm_file_to_image(data->mlx, "loading_img.xpm", &img_w, &img_h);
	if (!img)
	{
		ft_putstr_fd("put_loading_screen error\n", 2);
		clean_exit(EXIT_FAILURE, data);
	}
	mlx_put_image_to_window(data->mlx, data->win, img,
		WIDTH / 2 - img_w / 2, HEIGHT / 2 - img_h / 2);
	mlx_destroy_image(data->mlx, img);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * MRT_PI / 180.0);
}
