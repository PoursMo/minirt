/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:49:41 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/13 11:42:14 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_color;

typedef struct s_ambiant_light
{
	float	ratio;
	t_color	color;
	t_color	scaled_color;
}	t_ambiant_light;

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	direction;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector3	position;
	float		brightness;
	t_color		color;
	t_color		scaled_color;
}	t_light;

typedef enum e_hit_pos
{
	NONE,
	TOP,
	BODY,
	BASE
}	t_hit_pos;

typedef struct s_sphere
{
	t_vector3	position;
	float		radius;
}	t_sphere;

typedef struct s_plane
{
	t_vector3	position;
	t_vector3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3	position;
	t_vector3	axis;
	float		radius;
	float		height;
	t_hit_pos	hit_pos;
}	t_cylinder;

typedef struct s_cone
{
	t_vector3	position;
	t_vector3	axis;
	float		radius;
	float		height;
	float		angle;
	t_hit_pos	hit_pos;
}	t_cone;

typedef enum e_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_shape_type;

typedef union u_shape_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
}	t_shape_data;

typedef struct s_shape
{
	t_shape_type	type;
	t_shape_data	data;
	t_color			color;
	t_img			*texture;
	t_img			*bump_map;
}	t_shape;

typedef struct s_scene
{
	t_ambiant_light	*ambiant_light;
	t_camera		*camera;
	t_list			*lights;
	t_list			*shapes;
}	t_scene;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

typedef struct s_ray_hit_info
{
	t_ray		*ray;
	t_vector3	position;
	t_vector3	normal;
	t_shape		*shape;
}	t_ray_hit_info;

typedef struct s_mrt_data
{
	void	*mlx;
	void	*win;
	t_scene	scene;
}	t_mrt_data;

typedef struct s_precomputed_camera
{
	t_vector3	origin;
	t_vector3	forward_vector;
	t_vector3	right_vector;
	t_vector3	up_vector;
	float		aspect_ratio;
	float		viewport_height;
	float		viewport_width;
}	t_precomputed_camera;

#endif