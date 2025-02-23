/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unique_getters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:28:50 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/23 15:37:11 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parsing_get_ambiant_lighting(char *line)
{
	if (get_scene()->ambiant_light)
		return (misconfiguration_error("ambiant lighting: duplicate"), -1);
	get_scene()->ambiant_light = malloc(sizeof(t_ambiant_light));
	if (!get_scene()->ambiant_light)
		return (perror("get_ambiant_lighting"), -1);
	if (parsing_get_float(&line, &get_scene()->ambiant_light->ratio, 0.0f, 1.0f) == -1
		|| parsing_get_color(&line, &get_scene()->ambiant_light->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("ambiant lighting: wrong parameters"), -1);
	return (0);
}

int	parsing_get_camera(char *line)
{
	if (get_scene()->camera)
		return (misconfiguration_error("camera: duplicate"), -1);
	get_scene()->camera = malloc(sizeof(t_camera));
	if (!get_scene()->camera)
		return (perror("get_camera"), -1);
	if (parsing_get_vector3(&line, &get_scene()->camera->position) == -1
		|| parsing_get_normalized_vector3(&line, &get_scene()->camera->direction) == -1
		|| parsing_get_int(&line, &get_scene()->camera->fov, 0, 180) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("camera: wrong parameters"), -1);
	return (0);
}

int	parsing_get_light(char *line)
{
	if (get_scene()->light)
		return (misconfiguration_error("light: duplicate"), -1);
	get_scene()->light = malloc(sizeof(t_light));
	if (!get_scene()->light)
		return (perror("get_light"), -1);
	if (parsing_get_vector3(&line, &get_scene()->light->position) == -1
		|| parsing_get_float(&line, &get_scene()->light->brightness, 0.0f, 1.0f) == -1
		|| parsing_get_color(&line, &get_scene()->light->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("light: wrong parameters"), -1);
	return (0);
}
