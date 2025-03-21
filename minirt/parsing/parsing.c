/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:51 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/14 14:03:07 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
precompute light
replace torus > cone
do cleanest parsing ever ?
with special perror ?
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
	else if (!ft_strncmp("co ", line, 3))
		return (parse_cone(line + 2, mrt_data));
	else if (!ft_strncmp("cu ", line, 3))
		return (parse_cube(line + 2, mrt_data));
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
