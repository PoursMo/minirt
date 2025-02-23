/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:25:36 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/23 15:52:34 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ** debug.c **
void print_scene(t_scene *scene);
// *************

// ** blblblbl.c **
void render_scene(t_mlx_data *data);
// ****************

int mrt_terminate(void *data)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data *)data;
	free_scene();
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->mlx);
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
	if (argc != 2)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), EXIT_FAILURE);
	if (parse_file(argv[argc - 1]) == -1)
		return (1);
	print_scene(get_scene()); // debug

	// // get endian
	// int local_endian;
	// int a = 0x11223344;
	// if (((unsigned char *)&a)[0] == 0x11)
	// 	local_endian = 1;
	// else
	// 	local_endian = 0;
	// printf(" => Local Endian : %d\n",local_endian);

	// initialize mlx stuff
	t_mlx_data data;
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