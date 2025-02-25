/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:48 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/25 23:44:32 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// parsing.c

int		parse_file(char *file, t_scene *scene);

// parsing_utils.c

float	mrt_atof(char **nptr);
int		mrt_atoi(char **nptr);
int		is_dot_rt_file(char *file);
int		is_valid_parameter(char **line);
int		is_valid_tail(char *line);

// parsing_utils2.c

void	misconfiguration_error(char *error);
int		check_scene(t_scene *scene);

// parsing_shape_getters.c

int		parsing_get_sphere(char *line, t_scene *scene);
int		parsing_get_plane(char *line, t_scene *scene);
int		parsing_get_cylinder(char *line, t_scene *scene);
int		parsing_get_torus(char *line, t_scene *scene);

// parsing_type_getters.c

int		parsing_get_float(char **line, float *target, float min, float max);
int		parsing_get_int(char **line, int *target, int min, int max);
int		parsing_get_color(char **line, t_color *target);
int		parsing_get_vector3(char **line, t_vector3 *target);
int		parsing_get_normalized_vector3(char **line, t_vector3 *target);

// parsing_unique_getters.c

int		parsing_get_ambiant_lighting(char *line, t_scene *scene);
int		parsing_get_camera(char *line, t_scene *scene);
int		parsing_get_light(char *line, t_scene *scene);

#endif