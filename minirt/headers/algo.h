/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:34 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/11 12:49:50 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

// rendering.c

void		render_scene(t_mrt_data *data);

// tracing.c

t_ray		get_ray(int x, int y, t_precomputed_camera *precomputed);
t_color		trace_ray(t_ray *ray, t_scene *scene);

// uvs.c

t_vector2	compute_shape_uv(t_ray_hit_info *info);

// intersections.c

int			intersect_shape(t_ray *ray, t_shape *shape, float *t);

// cylinder.c

void		check_for_cylinder_len(t_cylinder *cylinder, t_ray *ray, float t[2],
				float *intersect_dist);
void		check_for_caps(t_ray *ray, t_cylinder *cylinder,
				float *intersect_dist);
// cone.c

void		check_for_cone_len(t_cone *cone, t_ray *ray, float t[2],
				float *intersect_dist);
void		check_for_cone_base(t_cone *cone, t_ray *ray,
				float *intersect_dist);
int			check_inside_cone(t_cone *cone, t_vector3 cam_proj,
				float dist_cam_axis);

// phong.c

t_color		apply_phong(t_scene *scene, t_ray_hit_info *hit_info);

// lighting.c

t_color		compute_ambiant(t_color base_color, t_ambiant_light *ambiant_light);
t_color		compute_diffuse(t_color base_color, t_light *light,
				t_ray *light_ray, t_vector3 normal);
t_color		compute_specular(t_light *light, t_ray *light_ray,
				t_ray_hit_info *hit_info, t_vector3 normal);

// normal.c

t_vector3	get_normal(t_shape *shape, t_vector3 point, t_ray *ray);

// bump.c

t_vector3	perturb_normal(t_vector2 uvs, t_ray_hit_info *hit_info);

#endif