/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:48:25 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/27 13:09:23 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// color.c

t_color		color_multiply(t_color a, t_color b);
t_color		color_add(t_color a, t_color b);
t_color		color_scale(t_color c, float scalar);

// vectors.c

t_vector3	v3_cross(t_vector3 a, t_vector3 b);
t_vector3	v3_scale(t_vector3 v, float scalar);
t_vector3	v3_add(t_vector3 a, t_vector3 b);
t_vector3	v3_subtract(t_vector3 a, t_vector3 b);
t_vector3	v3_normalize(t_vector3 v);

// vectors2.c

float		v3_get_magnitude(t_vector3 v);
float		v3_dot(t_vector3 a, t_vector3 b);
t_vector3	v3_up(void);
t_vector3	v3_reflect(t_vector3 v, t_vector3 normal);
t_vector3	v3_negate(t_vector3 v);

// utils.c

void		place_pixel_in_mlx_img(t_img *img, int x, int y, t_color color);
void		clean_exit(int status, t_mrt_data *data);
int			mrt_terminate(void *data);
int			handle_key(int keycode, void *data);
void		free_scene(t_scene *scene);

// utils2.c

void		put_loading_screen(t_mrt_data *data);

#endif