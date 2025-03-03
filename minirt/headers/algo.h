/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:34 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 16:38:38 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

// uvs.c

t_vector2	compute_shape_uv(t_ray_hit_info *info);

// intersections.c

int			intersect_shape(t_ray *ray, t_shape *shape, float *t);

// phong.c

t_color		apply_phong(t_scene *scene, t_ray_hit_info *hit_info);

// lighting.c

t_color		compute_ambiant(t_color base_color, t_ambiant_light *ambiant_light);
t_color		compute_diffuse(t_color base_color, t_light *light,
				t_ray *light_ray, t_vector3 normal);
t_color		compute_specular(t_light *light, t_ray *light_ray,
				t_ray_hit_info *hit_info, t_vector3 normal);

// normal.c

t_vector3 get_normal(t_shape *shape, t_vector3 point, t_ray *ray);

#endif