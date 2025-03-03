/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:25:36 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 16:38:32 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void render_scene(t_mrt_data *data)
{
	t_img *img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!img)
    {
    	ft_putstr_fd("mlx_new_image error\n", 2);
    	clean_exit(EXIT_FAILURE, data);
    }
	fill_img(img, &data->scene);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}

int	main(int argc, char **argv)
{
	t_mrt_data	data;

	ft_memset(&data, 0, sizeof(t_mrt_data));
	if (argc != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), EXIT_FAILURE);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("mlx_init error\n", 2);
		clean_exit(EXIT_FAILURE, &data);
	}
	if (parse_file(argv[argc - 1], &data) == -1)
		clean_exit(EXIT_FAILURE, &data);
	print_scene(&data.scene); // debug
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	if (!data.win)
	{
		ft_putstr_fd("mlx_new_window error\n", 2);
		clean_exit(EXIT_FAILURE, &data);
	}
	put_loading_screen(&data);
	render_scene(&data);
	mlx_hook(data.win, DestroyNotify, 0, mrt_terminate, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
}
