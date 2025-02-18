/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:57:10 by aloubry           #+#    #+#             */
/*   Updated: 2025/02/15 15:06:39 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_atoi(char **nptr)
{
	int	mult;
	int	num;

	mult = 1;
	while (**nptr && ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '+' || **nptr == '-')
	{
		if (**nptr == '-')
			mult = -1;
		(*nptr)++;
	}
	num = 0;
	while (**nptr && ft_isdigit(**nptr))
	{
		num = num * 10 + (**nptr - 48);
		(*nptr)++;
	}
	return (num * mult);
}

float mrt_atof(char **nptr)
{
	float whole;
	float frac;
	float divisor;
	int mult;

	while (**nptr && ft_isspace(**nptr))
		(*nptr)++;
	mult = 1;
	if (**nptr == '+' || **nptr == '-')
	{
		if (**nptr == '-')
			mult = -1;
		(*nptr)++;
	}
	whole = 0;
	while (**nptr && ft_isdigit(**nptr))
	{
		whole = whole * 10 + (**nptr - '0');
		(*nptr)++;
	}
	frac = 0.0f;
	if (**nptr == '.')
	{
		(*nptr)++;
		divisor = 10.0f;
		while (**nptr && ft_isdigit(**nptr))
		{
			frac += (**nptr - '0') / divisor;
			divisor *= 10.0f;
			(*nptr)++;
		}
	}
	return ((whole + frac) * mult);
}