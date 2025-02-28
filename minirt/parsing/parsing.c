/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:51 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:31:05 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Torus:
identifier: to
x, y, z coordinates of the sphere center
3D normalized orientation vector, in range [-1,1] for each x, y, z axis
radius 1
radius 2
R,G,B colors in range [0-255]

Light:
identifier: l instead of L


take shininess as parameter for shapes ?
do cleanest parsing ever ?
with special perror ?
and usage print ?
*/

static int	parse_line(char *line, t_mrt_data *mrt_data)
{
	if (!ft_strncmp("A ", line, 2))
		return (parse_ambiant_lighting(line + 1, &mrt_data->scene));
	else if (!ft_strncmp("C ", line, 2))
		return (parse_camera(line + 1, &mrt_data->scene));
	else if (!ft_strncmp("l ", line, 2))
		return (parse_light(line + 1, &mrt_data->scene));
	else if (!ft_strncmp("sp ", line, 3))
		return (parse_sphere(line + 2, mrt_data));
	else if (!ft_strncmp("pl ", line, 3))
		return (parse_plane(line + 2, mrt_data));
	else if (!ft_strncmp("cy ", line, 3))
		return (parse_cylinder(line + 2, mrt_data));
	else if (!ft_strncmp("to ", line, 3))
		return (parse_torus(line + 2, mrt_data));
	else
		return (misconfiguration_error("unkown type identifier"), -1);
}

int	parse_file(char *file, t_mrt_data *mrt_data)
{
	int		fd;
	char	*line;
	int		i;

	if (!check_file_extension(file, ".rt"))
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
			if (parse_line(line + i, mrt_data) == -1)
				return (free(line), close(fd), -1);
		free(line);
	}
	close(fd);
	return (check_scene(&mrt_data->scene));
}
