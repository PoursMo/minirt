/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:53:25 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/15 15:49:30 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene *get_scene()
{
	static t_scene scene;
	return &scene;
}

void free_scene()
{
	if (get_scene()->ambiant_light)
		free(get_scene()->ambiant_light);
	if (get_scene()->camera)
		free(get_scene()->camera);
	if (get_scene()->light)
		free(get_scene()->light);
	// shapes
}