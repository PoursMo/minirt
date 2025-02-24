/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:25:36 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 14:17:08 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ** debug.c **
void print_scene(t_scene *scene);
// *************

int mrt_terminate(void *data)
{
	t_mrt_data *mrt_data;

	mrt_data = (t_mrt_data *)data;
	free_scene(&mrt_data->scene);
	mlx_destroy_window(mrt_data->mlx, mrt_data->win);
	mlx_destroy_display(mrt_data->mlx);
	free(mrt_data->mlx);
	exit(EXIT_SUCCESS);
}

int handle_key(int keycode, void *data)
{
	if (keycode == ESC_KEY)
		mrt_terminate(data);
	return (0);
}

int main(int argc, char **argv)
{
	t_mrt_data data;
	
	if (argc != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), EXIT_FAILURE);
	if (parse_file(argv[argc - 1], &data.scene) == -1)
		return (1);
	print_scene(&data.scene); // debug

	// // get endian
	// int local_endian;
	// int a = 0x11223344;
	// if (((unsigned char *)&a)[0] == 0x11)
	// 	local_endian = 1;
	// else
	// 	local_endian = 0;
	// printf(" => Local Endian : %d\n",local_endian);

	// initialize mlx stuff
	if (!(data.mlx = mlx_init()))
    {
    	printf(" !! KO !!\n");
    	exit(1); // do clean exit
    }
	if (!(data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT")))
    {
    	printf(" !! KO !!\n");
    	exit(1); // do clean exit
    }
	render_scene(&data);
	mlx_hook(data.win, DestroyNotify, 0, mrt_terminate, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
}