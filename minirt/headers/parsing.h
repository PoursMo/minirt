/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:48 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/14 13:56:39 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// parsing.c

int		parse_file(char *file, t_mrt_data *mrt_data);

// parsing_utils.c

float	mrt_atof(char **nptr);
int		mrt_atoi(char **nptr);
int		check_file_extension(char *file, char *extension);
int		is_valid_parameter(char **line);
int		is_valid_tail(char *line);

// parsing_utils2.c

void	misconfiguration_error(char *error);
int		check_scene(t_scene *scene);

// parsing_shape_getters.c

int		parse_sphere(char *line, t_mrt_data *mrt_data);
int		parse_plane(char *line, t_mrt_data *mrt_data);
int		parse_cylinder(char *line, t_mrt_data *mrt_data);
int		parse_cone(char *line, t_mrt_data *mrt_data);
int		parse_cube(char *line, t_mrt_data *mrt_data);

// parsing_type_getters.c

int		parse_float(char **line, float *target, float min, float max);
int		parse_int(char **line, int *target, int min, int max);
int		parse_color(char **line, t_color *target);
int		parse_vector3(char **line, t_vector3 *target);
int		parse_normalized_vector3(char **line, t_vector3 *target);

// parsing_type_getters2.c

int		parse_img(char **line, t_img **img, void *mlx);

// parsing_unique_getters.c

int		parse_ambiant_lighting(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

#endif