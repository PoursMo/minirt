/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:33:43 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/22 20:33:50 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	misconfiguration_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putchar_fd('\n', 2);
	}
}
