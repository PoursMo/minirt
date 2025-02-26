/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittet <lpittet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:51:34 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/26 15:17:05 by lpittet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

void	render_scene(t_mrt_data *data);

// intersections.c

int		intersect_plane(t_ray *ray, t_plane *plane, float *intersect_dist);
int 	intersect_sphere(t_ray *ray, t_sphere *sphere, float *intersect_dist);

#endif