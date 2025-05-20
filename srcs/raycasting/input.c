/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:10:29 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/20 13:47:52 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../includes/utils.h"

int	control_input4(t_data *data, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	if (data->keys.right)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-rotspeed) - data->diry * sin(-rotspeed);
		data->diry = olddirx
			* sin(-rotspeed) + data->diry * cos(-rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex
			* cos(-rotspeed) - data->planey * sin(-rotspeed);
		data->planey = oldplanex
			* sin(-rotspeed) + data->planey * cos(-rotspeed);
	}
	render(data);
	return (0);
}

int	control_input3(t_data *data, double rotspeed)
{
	double	olddirx;
	double	oldplanex;

	if (data->keys.left)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
		data->diry = olddirx * sin(rotspeed) + data->diry * cos(rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex
			* cos(rotspeed) - data->planey * sin(rotspeed);
		data->planey = oldplanex
			* sin(rotspeed) + data->planey * cos(rotspeed);
	}
	return (control_input4(data, rotspeed));
}

int	control_input2(t_data *data, double movespeed, double rotspeed)
{
	if (data->keys.d)
	{
		if (data->config.map_lines[(int)(data->posy)]
			[(int)(data->posx + data->planex * movespeed)] == '0')
			data->posx += data->planex * movespeed;
		if (data->config.map_lines[(int)(data->posy + data->planey * movespeed)]
			[(int)(data->posx)] == '0')
			data->posy += data->planey * movespeed;
	}
	if (data->keys.a)
	{
		if (data->config.map_lines[(int)(data->posy)]
			[(int)(data->posx - data->planex * movespeed)] == '0')
			data->posx -= data->planex * movespeed;
		if (data->config.map_lines[(int)(data->posy - data->planey * movespeed)]
			[(int)(data->posx)] == '0')
			data->posy -= data->planey * movespeed;
	}
	return (control_input3(data, rotspeed));
}

int	control_input(t_data *data)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.03f;
	rotspeed = 0.01f;
	if (data->keys.w)
	{
		if (data->config.map_lines[(int)(data->posy)]
			[(int)(data->posx + data->dirx * movespeed)] == '0')
			data->posx += data->dirx * movespeed;
		if (data->config.map_lines[(int)(data->posy + data->diry * movespeed)]
			[(int)(data->posx)] == '0')
			data->posy += data->diry * movespeed;
	}
	if (data->keys.s)
	{
		if (data->config.map_lines[(int)(data->posy)]
			[(int)(data->posx - data->dirx * movespeed)] == '0')
			data->posx -= data->dirx * movespeed;
		if (data->config.map_lines[(int)(data->posy - data->diry * movespeed)]
			[(int)(data->posx)] == '0')
			data->posy -= data->diry * movespeed;
	}
	return (control_input2(data, movespeed, rotspeed));
}
