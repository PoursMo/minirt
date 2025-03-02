/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:33:43 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 17:52:22 by aloubry          ###   ########.fr       */
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

int	check_scene(t_scene *scene)
{
	if (!scene->ambiant_light)
		return (misconfiguration_error("ambiant light missing"), -1);
	if (!scene->camera)
		return (misconfiguration_error("camera missing"), -1);
	return (0);
}
