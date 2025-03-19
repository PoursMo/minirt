/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:53 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/19 09:51:06 by lpittet          ###   ########.fr       */
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
# define EPSILON 1e-3

#endif