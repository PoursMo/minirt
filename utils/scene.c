/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:53:25 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/22 16:13:31 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

void	free_scene(void)
{
	if (get_scene()->ambiant_light)
		free(get_scene()->ambiant_light);
	if (get_scene()->camera)
		free(get_scene()->camera);
	if (get_scene()->light)
		free(get_scene()->light);
	if (get_scene()->spheres)
		ft_lstclear(&get_scene()->spheres, free);
	if (get_scene()->planes)
		ft_lstclear(&get_scene()->planes, free);
	if (get_scene()->cylinders)
		ft_lstclear(&get_scene()->cylinders, free);
}
