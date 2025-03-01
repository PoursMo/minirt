/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:34 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/01 13:47:20 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

void	render_scene(t_mrt_data *data);

// uvs.c

t_vector2	compute_shape_uv(t_ray_hit_info *info);

// intersections.c

int	intersect_shape(t_ray *ray, t_shape *shape, float *t);

// phong.c

t_color apply_phong(t_scene *scene, t_ray_hit_info *hit_info);

#endif