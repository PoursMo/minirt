/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shape_getters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:27:59 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 15:03:04 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	add_shape_to_scene(t_shape *shape, t_scene *scene)
{
	t_list	*shape_list;

	shape_list = ft_lstnew(shape);
	if (!shape_list)
		return (perror("add_shape_to_scene"), free(shape), -1);
	ft_lstadd_back(&scene->shapes, shape_list);
	return (0);
}

int	parse_sphere(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;
	float		diameter;

	shape = calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_sphere"), -1);
	shape->type = SPHERE;
	if (parse_vector3(&line, &shape->data.sphere.position) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("sphere: wrong parameters"), free_shape(shape, mrt_data->mlx), -1);
	shape->data.sphere.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_plane(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;

	shape = calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_plane"), -1);
	shape->type = PLANE;
	if (parse_vector3(&line, &shape->data.plane.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.plane.normal) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("plane: wrong parameters"), free_shape(shape, mrt_data->mlx), -1);
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_cylinder(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;
	float		diameter;

	shape = calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_cylinder"), -1);
	shape->type = CYLINDER;
	if (parse_vector3(&line, &shape->data.cylinder.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.cylinder.axis) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_float(&line, &shape->data.cylinder.height, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cylinder: wrong parameters"), free_shape(shape, mrt_data->mlx), -1);
	shape->data.cylinder.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_cone(char *line, t_mrt_data *mrt_data)
{
	t_shape	*shape;
	float	diameter;

	shape = calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_cone"), -1);
	shape->type = CONE;
	if (parse_vector3(&line, &shape->data.cone.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.cone.axis) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_float(&line, &shape->data.cone.height, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cone: wrong parameters"), free_shape(shape, mrt_data->mlx), -1);
	shape->data.cone.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, &mrt_data->scene));
}
