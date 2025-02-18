/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:18:48 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/15 16:23:43 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

// parsing.c

int parse_file(char *file);

// parsing_utils.c

float mrt_atof(char **nptr);
int	mrt_atoi(char **nptr);

#endif