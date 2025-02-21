/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:51 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/21 14:15:56 by aloubry          ###   ########.fr       */
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

int	is_valid_parameter(char **line)
{
	return (*((*line) - 1) == ' '
		&& (!ft_isdigit(**line) || **line != '-' || **line != '+'));
}

int is_valid_tail(char *line)
{
	while (*line != '\n' && *line != EOF)
	{
		if (*line == ' ')
			line++;
		else
			return (0);
	}
	return (1);
}

int	parsing_get_float(char **line, float *target, float min, float max)
{
	while (**line == ' ')
		(*line)++;
	if (!is_valid_parameter(line))
		return (-1);
	*target = mrt_atof(line);
	if (*target < min || *target > max)
		return (-1);
	return (0);
}

int	parsing_get_int(char **line, int *target, int min, int max)
{
	while (**line == ' ')
		(*line)++;
	if (!is_valid_parameter(line))
		return (-1);
	*target = mrt_atoi(line);
	if (*target < min || *target > max)
		return (-1);
	return (0);
}

int	parsing_get_color(char **line, t_color *target)
{
	while (**line == ' ')
		(*line)++;
	if (!is_valid_parameter(line))
		return (-1);
	target->red = mrt_atoi(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	target->green = mrt_atoi(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	target->blue = mrt_atoi(line);
	return (0);
}

int	parsing_get_vector3(char **line, t_vector3 *target)
{
	while (**line == ' ')
		(*line)++;
	if (!is_valid_parameter(line))
		return (-1);
	target->x = mrt_atof(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	target->y = mrt_atof(line);
	if (**line == ',')
		(*line)++;
	else
		return (-1);
	target->z = mrt_atof(line);
	return (0);
}

int	get_ambiant_lighting(char *line)
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

int	get_camera(char *line)
{
	if (get_scene()->camera)
		return (misconfiguration_error("camera: duplicate"), -1);
	get_scene()->camera = malloc(sizeof(t_camera));
	if (!get_scene()->camera)
		return (perror("get_camera"), -1);
	if (parsing_get_vector3(&line, &get_scene()->camera->position) == -1
		|| parsing_get_vector3(&line, &get_scene()->camera->direction) == -1 // normalized
		|| parsing_get_int(&line, &get_scene()->camera->fov, 0, 180) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("camera: wrong parameters"), -1);
	return (0);
}

int	get_light(char *line)
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

int	get_sphere(char *line)
{
	t_sphere	*sphere;
	t_list		*sphere_list;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (perror("get_sphere"), -1);
	if (parsing_get_vector3(&line, &sphere->position) == -1
		|| parsing_get_float(&line, &sphere->diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &sphere->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("sphere: wrong parameters"), free(sphere), -1);
	sphere_list = ft_lstnew(sphere);
	if (!sphere_list)
		return (perror("get_sphere"), free(sphere), -1);
	ft_lstadd_back(&get_scene()->spheres, sphere_list);
	return (0);
}

int	get_plane(char *line)
{
	t_plane	*plane;
	t_list	*plane_list;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (perror("get_plane"), -1);
	if (parsing_get_vector3(&line, &plane->position) == -1
		|| parsing_get_vector3(&line, &plane->normal) == -1 // normalized
		|| parsing_get_color(&line, &plane->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("plane: wrong parameters"), free(plane), -1);
	plane_list = ft_lstnew(plane);
	if (!plane_list)
		return (perror("get_plane"), free(plane), -1);
	ft_lstadd_back(&get_scene()->planes, plane_list);
	return (0);
}

int	get_cylinder(char *line)
{
	t_cylinder	*cylinder;
	t_list		*cylinder_list;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (perror("get_cylinder"), -1);
	if (parsing_get_vector3(&line, &cylinder->position) == -1
		|| parsing_get_vector3(&line, &cylinder->axis) == -1 // normalized
		|| parsing_get_float(&line, &cylinder->diameter, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_float(&line, &cylinder->height, 0.0f, __FLT_MAX__) == -1
		|| parsing_get_color(&line, &cylinder->color) == -1
		|| !is_valid_tail(line))
		return (misconfiguration_error("cylinder: wrong parameters"), free(cylinder), -1);
	cylinder_list = ft_lstnew(cylinder);
	if (!cylinder_list)
		return (perror("get_cylinder"), free(cylinder), -1);
	ft_lstadd_back(&get_scene()->cylinders, cylinder_list);
	return (0);
}

int	parse_line(char *line)
{
	if (!ft_strncmp("A ", line, 2))
		return (get_ambiant_lighting(line + 1));
	else if (!ft_strncmp("C ", line, 2))
		return (get_camera(line + 1));
	else if (!ft_strncmp("L ", line, 2))
		return (get_light(line + 1));
	else if (!ft_strncmp("sp ", line, 3))
		return (get_sphere(line + 2));
	else if (!ft_strncmp("pl ", line, 3))
		return (get_plane(line + 2));
	else if (!ft_strncmp("cy ", line, 3))
		return (get_cylinder(line + 2));
	else
		return (misconfiguration_error("unkown type identifier"), -1);
}

int	is_dot_rt_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len <= 3)
		return (0);
	if (!ft_strncmp(file + len - 3, ".rt", 3))
		return (1);
	return (0);
}

int	parse_file(char *file)
{
	int		fd;
	char	*line;
	int		i;

	if (!is_dot_rt_file(file))
		return (misconfiguration_error("invalid file format"), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), -1);
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
