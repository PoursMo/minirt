/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:33:43 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/14 14:02:30 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	misconfiguration_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putchar_fd('\n', 2);
	}
}

int	check_scene(t_scene *scene)
{
	if (!scene->ambiant_light)
		return (misconfiguration_error("ambiant light missing"), -1);
	if (!scene->camera)
		return (misconfiguration_error("camera missing"), -1);
	return (0);
}

int	add_shape_to_scene(t_shape *shape, t_scene *scene)
{
	t_list	*shape_list;

	shape_list = ft_lstnew(shape);
	if (!shape_list)
		return (perror("add_shape_to_scene"), free(shape), -1);
	ft_lstadd_back(&scene->shapes, shape_list);
	return (0);
}
