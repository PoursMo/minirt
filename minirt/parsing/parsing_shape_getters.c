/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shape_getters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:27:59 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/23 15:37:01 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parsing_get_sphere(char *line)
{
	t_sphere	*sphere;
	t_list		*sphere_list;
	float		diameter;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("get_sphere"), -1);
	if (parsing_get_vector3(&line, &sphere->position) == -1
		|| parsing_get_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &sphere->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("sphere: wrong parameters"), free(sphere), -1);
	sphere->radius = diameter / 2.0f;
	sphere_list = ft_lstnew(sphere);
	if (!sphere_list)
		return (perror("get_sphere"), free(sphere), -1);
	ft_lstadd_back(&get_scene()->spheres, sphere_list);
	return (0);
}

int	parsing_get_plane(char *line)
{
	t_plane	*plane;
	t_list	*plane_list;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (perror("get_plane"), -1);
	if (parsing_get_vector3(&line, &plane->position) == -1
		|| parsing_get_normalized_vector3(&line, &plane->normal) == -1
		|| parsing_get_color(&line, &plane->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("plane: wrong parameters"), free(plane), -1);
	plane_list = ft_lstnew(plane);
	if (!plane_list)
		return (perror("get_plane"), free(plane), -1);
	ft_lstadd_back(&get_scene()->planes, plane_list);
	return (0);
}

int	parsing_get_cylinder(char *line)
{
	t_cylinder	*cylinder;
	t_list		*cylinder_list;
	float		diameter;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (perror("get_cylinder"), -1);
	if (parsing_get_vector3(&line, &cylinder->position) == -1
		|| parsing_get_normalized_vector3(&line, &cylinder->axis) == -1
		|| parsing_get_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_float(&line, &cylinder->height, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &cylinder->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cylinder: wrong parameters"), free(cylinder), -1);
	cylinder->radius = diameter / 2.0f;
	cylinder_list = ft_lstnew(cylinder);
	if (!cylinder_list)
		return (perror("get_cylinder"), free(cylinder), -1);
	ft_lstadd_back(&get_scene()->cylinders, cylinder_list);
	return (0);
}
