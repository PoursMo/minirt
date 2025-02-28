/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:34 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/28 14:36:15 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

void	render_scene(t_mrt_data *data);

// intersections.c

int		intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist);
int 	intersect_sphere(t_ray *ray, t_sphere *sphere, float *intersect_dist);

// phong.c

t_color apply_phong(t_scene *scene, t_ray_hit_info *hit_info);

#endif