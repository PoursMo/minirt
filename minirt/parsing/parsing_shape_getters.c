/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_shape_getters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:27:59 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/19 09:14:55 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;
	float		diameter;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_sphere"), -1);
	shape->type = SPHERE;
	if (parse_vector3(&line, &shape->data.sphere.position) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("sphere: wrong parameters"),
			free_shape(shape, mrt_data->mlx), -1);
	shape->data.sphere.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_plane(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_plane"), -1);
	shape->type = PLANE;
	if (parse_vector3(&line, &shape->data.plane.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.plane.normal) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("plane: wrong parameters"),
			free_shape(shape, mrt_data->mlx), -1);
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_cylinder(char *line, t_mrt_data *mrt_data)
{
	t_shape		*shape;
	float		diameter;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_cylinder"), -1);
	shape->type = CYLINDER;
	if (parse_vector3(&line, &shape->data.cylinder.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.cylinder.axis) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_float(&line, &shape->data.cylinder.height, 0.0f, __FLT_MAX__)
		== -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cylinder: wrong parameters"),
			free_shape(shape, mrt_data->mlx), -1);
	shape->data.cylinder.radius = diameter / 2.0f;
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_cone(char *line, t_mrt_data *mrt_data)
{
	t_shape	*shape;
	float	diameter;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_cone"), -1);
	shape->type = CONE;
	if (parse_vector3(&line, &shape->data.cone.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.cone.axis) == -1
		|| parse_float(&line, &diameter, 0.0f, __FLT_MAX__) == -1
		|| parse_float(&line, &shape->data.cone.height, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cone: wrong parameters"),
			free_shape(shape, mrt_data->mlx), -1);
	shape->data.cone.radius = diameter / 2.0f;
	shape->data.cone.angle = atan(shape->data.cone.radius
			/ shape->data.cone.height);
	return (add_shape_to_scene(shape, &mrt_data->scene));
}

int	parse_cube(char *line, t_mrt_data *mrt_data)
{
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (perror("parse_cube"), -1);
	shape->type = CUBE;
	if (parse_vector3(&line, &shape->data.cube.position) == -1
		|| parse_normalized_vector3(&line, &shape->data.cube.axis) == -1
		|| parse_float(&line, &shape->data.cube.size, 0.0f, __FLT_MAX__) == -1
		|| parse_color(&line, &shape->color) == -1
		|| parse_img(&line, &shape->texture, mrt_data->mlx) == -1
		|| parse_img(&line, &shape->bump_map, mrt_data->mlx) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cube: wrong parameters"),
			free_shape(shape, mrt_data->mlx), -1);
	get_normals(&shape->data.cube, shape->data.cube.normals);
	return (add_shape_to_scene(shape, &mrt_data->scene));
}
