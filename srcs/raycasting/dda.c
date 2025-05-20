/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:28:24 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 19:34:35 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_window(t_texture *texture)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			draw_pixel(texture, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	init_step(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
	}
}

void	init_dda(t_data *data, int x)
{
	data->camerax = 2 * x / (double)WIDTH - 1;
	data->raydirx = data->dirx + data->planex * data->camerax;
	data->raydiry = data->diry + data->planey * data->camerax;
	data->mapx = (int)data->posx;
	data->mapy = (int)data->posy;
	if (data->raydirx == 0)
		data->deltadistx = 1e30;
	else
		data->deltadistx = fabs(1 / data->raydirx);
	if (data->raydiry == 0)
		data->deltadisty = 1e30;
	else
		data->deltadisty = fabs(1 / data->raydiry);
	data->hit = 0;
	init_step(data);
}

void	dda_loop(t_data *data)
{
	if (data->sidedistx < data->sidedisty)
	{
		data->sidedistx += data->deltadistx;
		data->mapx += data->stepx;
		data->side = 0;
	}
	else
	{
		data->sidedisty += data->deltadisty;
		data->mapy += data->stepy;
		data->side = 1;
	}
	if ((data->config.map_lines[data->mapy][data->mapx] == '1') ||
		(data->config.map_lines[data->mapy][data->mapx] == 'D'))
	{
		if (data->config.map_lines[data->mapy][data->mapx] == 'D' &&
			door_is_open(data))
			data->hit = 0;
		else
			data->hit = 1;
	}
}
