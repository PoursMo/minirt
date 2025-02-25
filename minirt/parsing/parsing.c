/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:51 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/26 00:03:25 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Torus:
identifier: to
x, y, z coordinates of the sphere center
3D normalized orientation vector, in range [-1,1] for each x, y, z axis
minor radius ?? diameter ??
major radius ?? diameter ??
R,G,B colors in range [0-255]

Light:
identifier: l instead of L
*/

int	parse_line(char *line, t_scene *scene)
{
	if (!ft_strncmp("A ", line, 2))
		return (parsing_get_ambiant_lighting(line + 1, scene));
	else if (!ft_strncmp("C ", line, 2))
		return (parsing_get_camera(line + 1, scene));
	else if (!ft_strncmp("l ", line, 2))
		return (parsing_get_light(line + 1, scene));
	else if (!ft_strncmp("sp ", line, 3))
		return (parsing_get_sphere(line + 2, scene));
	else if (!ft_strncmp("pl ", line, 3))
		return (parsing_get_plane(line + 2, scene));
	else if (!ft_strncmp("cy ", line, 3))
		return (parsing_get_cylinder(line + 2, scene));
	else if (!ft_strncmp("to ", line, 3))
		return (parsing_get_torus(line + 2, scene));
	else
		return (misconfiguration_error("unkown type identifier"), -1);
}

int	parse_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		i;

	if (!is_dot_rt_file(file))
		return (misconfiguration_error("invalid file format"), -1);
	fd = open(file, O_RDWR);
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
			if (parse_line(line + i, scene) == -1)
				return (free_scene(scene), free(line), close(fd), -1);
		free(line);
	}
	close(fd);
	return (check_scene(scene));
}
