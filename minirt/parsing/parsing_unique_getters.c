/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unique_getters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:28:50 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/11 12:55:07 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambiant_lighting(char *line, t_scene *scene)
{
	if (scene->ambiant_light)
		return (misconfiguration_error("ambiant lighting: duplicate"), -1);
	scene->ambiant_light = malloc(sizeof(t_ambiant_light));
	if (!scene->ambiant_light)
		return (perror("get_ambiant_lighting"), -1);
	if (parse_float(&line, &scene->ambiant_light->ratio, 0.0f, 1.0f) == -1
		|| parse_color(&line, &scene->ambiant_light->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("ambiant lighting: wrong parameters"),
			-1);
	scene->ambiant_light->scaled_color
		= color_scale(scene->ambiant_light->color, scene->ambiant_light->ratio);
	return (0);
}

int	parse_camera(char *line, t_scene *scene)
{
	if (scene->camera)
		return (misconfiguration_error("camera: duplicate"), -1);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (perror("get_camera"), -1);
	if (parse_vector3(&line, &scene->camera->position) == -1
		|| parse_normalized_vector3(&line, &scene->camera->direction) == -1
		|| parse_int(&line, &scene->camera->fov, 0, 180) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("camera: wrong parameters"), -1);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	t_light	*light;
	t_list	*lights_list;

	light = malloc(sizeof(t_light));
	if (!light)
		return (perror("get_light"), -1);
	if (parse_vector3(&line, &light->position) == -1
		|| parse_float(&line, &light->brightness, 0.0f, 1.0f) == -1
		|| parse_color(&line, &light->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("light: wrong parameters"), -1);
	lights_list = ft_lstnew(light);
	if (!lights_list)
		return (perror("parse_light"), free(light), -1);
	light->scaled_color = color_scale(light->color, light->brightness);
	ft_lstadd_back(&scene->lights, lights_list);
	return (0);
}
