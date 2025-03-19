/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_datas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubry <aloubry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:00:41 by aloubry           #+#    #+#             */
/*   Updated: 2025/03/19 11:18:08 by aloubry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_thread_data(t_thread_data *datas, int i, int y_step,
	int *leftover)
{
	if (i == 0)
		datas[i].y_stop = y_step;
	else
		datas[i].y_stop = datas[i - 1].y_stop + y_step;
	if (*leftover)
	{
		datas[i].y_stop++;
		(*leftover)--;
	}
	if (i == 0)
		datas[i].y_start = 0;
	else
		datas[i].y_start = datas[i - 1].y_stop;
}

void	fill_thread_datas(t_thread_data *datas, t_img *img, t_scene *scene,
	t_precomputed_camera *precomputed)
{
	int	y_step;
	int	leftover;
	int	i;

	y_step = img->height / NB_THREADS;
	leftover = img->height % NB_THREADS;
	i = 0;
	while (i < NB_THREADS)
	{
		fill_thread_data(datas, i, y_step, &leftover);
		datas[i].img = img;
		datas[i].scene = scene;
		datas[i].precomputed = precomputed;
		i++;
	}
}
