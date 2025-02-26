/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type_getters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:25:55 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/26 15:17:05 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	parsing_get_normalized_vector3(char **line, t_vector3 *target)
{
	while (**line == ' ')
		(*line)++;
	if (!is_valid_parameter(line))
		return (-1);
	target->x = mrt_atof(line);
	if (**line == ',' && target->x >= -1.0 && target->x <= 1.0)
		(*line)++;
	else
		return (-1);
	target->y = mrt_atof(line);
	if (**line == ',' && target->y >= -1.0 && target->y <= 1.0)
		(*line)++;
	else
		return (-1);
	target->z = mrt_atof(line);
	if (target->z < -1.0 || target->z > 1.0)
		return (-1);
	*target = v3_normalize(*target);
	return (0);
}
