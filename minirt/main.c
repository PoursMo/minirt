/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:25:36 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 18:58:27 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ** debug.c **
void print_scene(t_scene *scene);
// *************

int main(int argc, char **argv)
{
	t_mrt_data data;
	
	ft_memset(&data, 0, sizeof(t_mrt_data));
	if (argc != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), EXIT_FAILURE);
	if (parse_file(argv[argc - 1], &data.scene) == -1)
		return (EXIT_FAILURE);
	print_scene(&data.scene); // debug

	// // get endian
	// int local_endian;
	// int a = 0x11223344;
	// if (((unsigned char *)&a)[0] == 0x11)
	// 	local_endian = 1;
	// else
	// 	local_endian = 0;
	// printf(" => Local Endian : %d\n",local_endian);

	if (!(data.mlx = mlx_init()))
    {
    	ft_putstr_fd("mlx_init error\n", 2);
    	clean_exit(EXIT_FAILURE, &data);
    }
	if (!(data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT")))
    {
    	ft_putstr_fd("mlx_new_window error\n", 2);
    	clean_exit(EXIT_FAILURE, &data);
    }
	// add loading screen ?
	render_scene(&data);
	mlx_hook(data.win, DestroyNotify, 0, mrt_terminate, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
}