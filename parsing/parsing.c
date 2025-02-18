/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:51 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/18 22:08:18 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void misconfiguration_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putchar_fd('\n', 2);
	}
}

int parsing_get_color(char **line, t_color *c)
{
	c->red = mrt_atoi(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	c->green = mrt_atoi(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	c->blue = mrt_atoi(line);
	if (!ft_isspace(**line))
		return (-1);
	return (0);
}

int parsing_get_vector3(char **line, t_vector3 *v3)
{
	v3->x = mrt_atof(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	v3->y = mrt_atof(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	v3->z = mrt_atof(line);
	if (!ft_isspace(**line))
		return (-1);
	return (0);
}

int get_ambiant_lighting(char *line)
{
	if (!*line)
		return (misconfiguration_error("ambiant lighting: no informations"), -1);
	if (get_scene()->ambiant_light)
		return (misconfiguration_error("ambiant lighting: duplicate"), -1);
	get_scene()->ambiant_light = malloc(sizeof(t_ambiant_light));
	if (!get_scene()->ambiant_light)
		return (perror("get_ambiant_lighting"), -1);
	get_scene()->ambiant_light->ratio = mrt_atof(&line);
	if (get_scene()->ambiant_light->ratio > 1.0f || get_scene()->ambiant_light->ratio < 0.0f)	
		return (misconfiguration_error("ambiant lighting: wrong ratio value"), -1);
	if (parsing_get_color(&line, &get_scene()->ambiant_light->color) == -1)
		return (misconfiguration_error("ambiant lighting: wrong color values"), -1);
	return (0);
}

int get_camera(char *line)
{
	if (!*line)
		return (misconfiguration_error("camera: no informations"), -1);
	if (get_scene()->camera)
		return (misconfiguration_error("camera: duplicate"), -1);
	get_scene()->camera = malloc(sizeof(t_camera));
	if (!get_scene()->camera)
		return (perror("get_camera"), -1);
	if (parsing_get_vector3(&line, &get_scene()->camera->position) == -1)
		return (misconfiguration_error("camera: wrong position values"), -1);
	if (parsing_get_vector3(&line, &get_scene()->camera->direction) == -1)
		return (misconfiguration_error("camera: wrong direction values"), -1);
	get_scene()->camera->fov = mrt_atoi(&line);
	if (get_scene()->camera->fov < 0 || get_scene()->camera->fov > 180)	
		return (misconfiguration_error("camera: wrong fov value"), -1);
	return (0);
}

int get_light(char *line)
{
	if (!*line)
		return (misconfiguration_error("light: no informations"), -1);
	if (get_scene()->light)
		return (misconfiguration_error("light: duplicate"), -1);
	get_scene()->light = malloc(sizeof(t_light));
	if (!get_scene()->light)
		return (perror("get_light"), -1);
	if (parsing_get_vector3(&line, &get_scene()->light->position) == -1)
		return (misconfiguration_error("light: wrong position values"), -1);
	get_scene()->light->brightness = mrt_atof(&line);
	if (get_scene()->light->brightness < 0.0f || get_scene()->light->brightness > 1.0f)	
		return (misconfiguration_error("light: wrong brightness value"), -1);
	if (parsing_get_color(&line, &get_scene()->light->color) == -1)
		return (misconfiguration_error("light: wrong color values"), -1);
	return (0);
}

int parse_line(char *line)
{
	if (!ft_strncmp("A ", line, 2))
		return (get_ambiant_lighting(line + 2));
	else if (!ft_strncmp("C ", line, 2))
		return (get_camera(line + 2));
	else if (!ft_strncmp("L ", line, 2))
		return (get_light(line + 2));
	else if (!ft_strncmp("sp ", line, 3))
		return (0); // change
	else if (!ft_strncmp("pl ", line, 3))
		return (0); // change
	else if (!ft_strncmp("cy ", line, 3))
		return (0); // change
	else
		return (misconfiguration_error("unkown type identifier"), -1);
}

int parse_file(char *file)
{
	int fd;
	char *line;
	int i;

	// check file is .rt
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i])
			if (parse_line(line + i) == -1)
				return (free_scene(), free(line), close(fd), -1); // free and close
		free(line);
	}
	close(fd); // err handling
	return (0);
}