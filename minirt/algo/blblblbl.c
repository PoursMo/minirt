/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blblblbl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:47:14 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/03 16:11:23 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_precomputed_camera	precompute_camera(t_camera *camera, t_img *img)
{
	t_precomputed_camera	result;

	result.right_vector = v3_normalize(v3_cross(v3_up(), camera->direction));
	result.up_vector = v3_cross(camera->direction, result.right_vector);
	result.aspect_ratio = (float)(img->width - 1) / (float)(img->height - 1); // -1 useful?
	result.viewport_height = 2 * tan(degrees_to_radians(camera->fov) / 2);
	result.viewport_width = result.aspect_ratio * result.viewport_height;
	return (result);
}

// returns 3d coordinates of a pixel in our world depending on camera
t_vector3	pixel_to_world_coordinates(t_camera *camera, t_precomputed_camera *precomputed_camera, int x, int y)
{
	float		u;
	float		v;
	t_vector3	pixel_world;

	u = (2 * (x + 0.5) / (float)WIDTH - 1) * precomputed_camera->viewport_width / 2;
	v = (1 - 2 * (y + 0.5) / (float)HEIGHT) * precomputed_camera->viewport_height / 2;
	pixel_world = v3_add(v3_add(v3_add(camera->position, v3_scale(precomputed_camera->right_vector, u)), v3_scale(precomputed_camera->up_vector, v)), camera->direction);
	return (pixel_world);
}

// returns ray for pixel x, y with normalized direction
t_ray	get_ray(int x, int y, t_precomputed_camera *precomputed, t_camera *camera)
{
	t_ray	ray;

	ray.origin = camera->position;
	ray.direction = v3_normalize(v3_subtract(pixel_to_world_coordinates(camera, precomputed, x, y), camera->position));
	return (ray);
}

t_vector3	cylinder_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3	plane_hit_axis;
	t_vector3	normal;

	if (v3_get_magnitude(v3_subtract(shape->data.cylinder.position, point))
		< shape->data.cylinder.radius
		|| v3_get_magnitude(v3_subtract(v3_add(shape->data.cylinder.position,
					v3_scale(shape->data.cylinder.axis,
					shape->data.cylinder.height)), point))
					< shape->data.cylinder.radius)
	{
		if (v3_dot(ray->direction, shape->data.cylinder.axis) >= 0)
			return (v3_scale(shape->data.cylinder.axis, -1));
		return (shape->data.cylinder.axis);
	}
	plane_hit_axis = v3_cross(shape->data.cylinder.axis,
		v3_subtract(point, shape->data.cylinder.position));
	normal = v3_cross(plane_hit_axis, shape->data.cylinder.axis);
	return (v3_normalize(normal));
}

t_vector3 get_normal(t_shape *shape, t_vector3 point, t_ray *ray)
{
	t_vector3 normal;

	(void)point;
	if (shape->type == SPHERE)
	{
		normal = v3_normalize(v3_subtract(point, shape->data.sphere.position));
	}
	else if (shape->type == PLANE)
	{
		normal = shape->data.plane.normal;
	}
	else if (shape->type == CYLINDER)
	{
		normal = cylinder_normal(shape, point, ray);
	}
	else if (shape->type == TORUS)
	{
		// implement
	}
	return (normal);
}

// t = intersection distance
// returns 0 if no intersection
// returns 1 if intersection, and fills hit_info if it it not NULL
int get_closest_shape_intersecting(t_ray *ray, t_list *shapes, t_ray_hit_info *hit_info)
{
	t_shape *closest_shape;
	float t;
	float closest_t;

	closest_shape = NULL;
	closest_t = __FLT_MAX__;
	while (shapes)
	{
		t_shape *shape = (t_shape *)shapes->content;
		if (shape->type == SPHERE && intersect_sphere(ray, &shape->data.sphere, &t) && t < closest_t)
		{
 			closest_t = t;
			closest_shape = shape;
		}
		else if (shape->type == PLANE && intersect_plane(ray, &shape->data.plane, &t) && t < closest_t)
		{
			closest_t = t;
			closest_shape = shape;
		}
		else if (shape->type == CYLINDER && intersect_cylinder(ray, &shape->data.cylinder, &t) && t < closest_t)
		{
			closest_t = t;
			closest_shape = shape;
		}
		else if (shape->type == TORUS)
		{
			// torus check
		}
		shapes = shapes->next;
	}
	if (closest_shape)
	{
		if (hit_info)
		{
			hit_info->position = v3_add(ray->origin, v3_scale(ray->direction, closest_t));
			hit_info->normal = get_normal(closest_shape, hit_info->position, ray);
			hit_info->shape = closest_shape;
		}
		return (1);
	}
	return (0);
}

t_color	trace_ray(t_ray *ray, t_scene *scene)
{
	t_color			color;
	t_ray_hit_info	hit_info;

	ft_memset(&color, 0, sizeof(t_color));
	if (get_closest_shape_intersecting(ray, scene->shapes, &hit_info))
	{
		color = apply_phong(scene, &hit_info);
	}
	return (color);
}

// fills img using rays
void fill_img(t_img *img, t_scene *scene)
{
	t_precomputed_camera precomputed;
	t_ray ray;
	t_color color;
	int x;
	int y;

	precomputed = precompute_camera(scene->camera, img);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			ray = get_ray(x, y, &precomputed, scene->camera);
			color = trace_ray(&ray, scene);
			place_pixel_in_mlx_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

// renders scene using mlx image
void render_scene(t_mrt_data *data)
{
	t_img *img;

	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!img)
    {
    	ft_putstr_fd("mlx_new_image error\n", 2);
    	clean_exit(EXIT_FAILURE, data);
    }
	fill_img(img, &data->scene);
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
	mlx_destroy_image(data->mlx, img);
}
