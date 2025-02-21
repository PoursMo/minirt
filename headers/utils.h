/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:48:25 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/21 14:50:49 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

// color.c

int rgb_to_int(unsigned char red, unsigned char green, unsigned char blue);
int t_color_to_int(t_color color);

// scene.c

t_scene *get_scene();
void free_scene();

#endif