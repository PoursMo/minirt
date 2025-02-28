/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type_getters2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:25:55 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:21:05 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*get_texture_file(char **line)
{
	int		size;
	int		i;
	char	*file;

	size = 0;
	while (*((*line) + size) != ' ' && *((*line) + size) != '\n' && *((*line) + size))
		size++;
	file = malloc(sizeof(char) * (size + 1));
	if (!file)
		return (perror("parse_file"), NULL);
	i = 0;
	while (i < size)
		file[i++] = *((*line)++);
	file[i] = '\0';
	return (file);
}

int	parse_img(char **line, t_img **img, void *mlx)
{
	char	*file;
	int		w;
	int		h;

	while (**line == ' ')
		(*line)++;
	if (*((*line) - 1) != ' ')
		return (-1);
	file = get_texture_file(line);
	if (!strncmp(file, "n", ft_strlen(file)))
		return (*img = NULL, free(file), 0);
	if (!check_file_extension(file, ".xpm") || access(file, R_OK) == -1)
		return (free(file), -1);
	*img = mlx_xpm_file_to_image(mlx, file, &w, &h);
	if (!*img)
		return (free(file), -1);
	free(file);
	return (0);
}
