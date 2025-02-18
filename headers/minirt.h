/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:53 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/15 15:53:23 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# define MRT_PI	3.14159265358979323846

typedef struct s_vector3
{
	float x;
	float y;
	float z;
} t_vector3;

typedef struct s_color
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
} t_color;

typedef struct s_ambiant_light
{
	float ratio;
	t_color color;
} t_ambiant_light;

typedef struct s_camera
{
	t_vector3 position;
	t_vector3 direction;
	int fov;
} t_camera;

typedef struct s_light
{
	t_vector3 position;
	float brightness;
	t_color color; // unused in mandatory
} t_light;

typedef struct s_sphere
{
	t_vector3 position;
	float radius; // work with diameter ?
	t_color color;
} t_sphere;

typedef struct s_plane
{
	t_vector3 position;
	t_vector3 normal;
	t_color color;
} t_plane;

typedef struct s_cylinder
{
	t_vector3 position;
	t_vector3 axis;
	float radius; // work with diameter ?
	float height;
	t_color color;
} t_cylinder;

typedef struct s_scene
{
	t_ambiant_light *ambiant_light;
	t_camera *camera;
	t_light *light;
	t_list *shapes;
} t_scene;

# include "parsing.h"
# include "utils.h"

#endif