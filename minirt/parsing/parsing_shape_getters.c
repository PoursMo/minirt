/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shape_getters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:27:59 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/24 13:35:44 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int add_shape_to_scene(t_shape *shape, t_scene *scene)
{
	t_list *shape_list;

	shape_list = ft_lstnew(shape);
	if (!shape_list)
		return (perror("add_shape_to_scene"), free(shape), -1);
	ft_lstadd_back(&scene->shapes, shape_list);
	return (0);
}

int	parsing_get_sphere(char *line, t_scene *scene)
{
	t_shape		*shape;
	float		diameter;

	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (perror("get_sphere"), -1);
	shape->type = SPHERE;
	if (parsing_get_vector3(&line, &shape->data.sphere.position) == -1
		|| parsing_get_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &shape->data.sphere.color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("sphere: wrong parameters"), free(shape), -1);
	shape->data.sphere.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, scene));
}

int	parsing_get_plane(char *line, t_scene *scene)
{
	t_shape		*shape;

	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (perror("get_plane"), -1);
	shape->type = PLANE;
	if (parsing_get_vector3(&line, &shape->data.plane.position) == -1
		|| parsing_get_normalized_vector3(&line, &shape->data.plane.normal) == -1
		|| parsing_get_color(&line, &shape->data.plane.color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("plane: wrong parameters"), free(shape), -1);
	return (add_shape_to_scene(shape, scene));
}

int	parsing_get_cylinder(char *line, t_scene *scene)
{
	t_shape		*shape;
	float		diameter;

	shape = malloc(sizeof(t_shape));
	if (!shape)
		return (perror("get_cylinder"), -1);
	shape->type = CYLINDER;
	if (parsing_get_vector3(&line, &shape->data.cylinder.position) == -1
		|| parsing_get_normalized_vector3(&line, &shape->data.cylinder.axis) == -1
		|| parsing_get_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_float(&line, &shape->data.cylinder.height, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &shape->data.cylinder.color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cylinder: wrong parameters"), free(shape), -1);
	shape->data.cylinder.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, scene));
}
