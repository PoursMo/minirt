/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:53 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/01 21:58:57 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# include "structs.h"
# include "parsing.h"
# include "utils.h"
# include "algo.h"

# define MRT_PI	3.14159265358979323846
# define ESC_KEY 65307
# define WIDTH 1000
# define HEIGHT 700
# define SHININESS 32
# define EPSILON 1e-4

// ** debug.c **
t_color map_v3_to_color(t_vector3 v);
void print_scene(t_scene *scene);
// *************

#endif