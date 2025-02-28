/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:58:59 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:23:11 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shape(t_shape *shape, void *mlx)
{
	if (shape->texture)
		mlx_destroy_image(mlx, shape->texture);
	if (shape->bump_map)
		mlx_destroy_image(mlx, shape->bump_map);
	free(shape);
}

static void	free_shapes(t_mrt_data *data)
{
	t_list	*lst;
	t_list	*temp;

	lst = data->scene.shapes;
	while (lst)
	{
		temp = lst->next;
		free_shape(lst->content, data->mlx);
		free(lst);
		lst = temp;
	}
}

static void	free_scene(t_mrt_data *data)
{
	if (data->scene.ambiant_light)
		free(data->scene.ambiant_light);
	if (data->scene.camera)
		free(data->scene.camera);
	if (data->scene.lights)
		ft_lstclear(&data->scene.lights, free);
	if (data->scene.shapes)
		free_shapes(data);
}

void	clean_exit(int status, t_mrt_data *data)
{
	free_scene(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(status);
}

int	mrt_terminate(void *data)
{
	t_mrt_data	*mrt_data;

	mrt_data = (t_mrt_data *)data;
	clean_exit(EXIT_SUCCESS, mrt_data);
	return (0);
}
