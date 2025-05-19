/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:10:29 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 14:32:39 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	on_press(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	if (keycode == 115)
		data->keys.s = 1;
	if (keycode == 100)
		data->keys.d = 1;
	if (keycode == 97)
		data->keys.a = 1;
	if (keycode == 65361)
		data->keys.left = 1;
	if (keycode == 65363)
		data->keys.right = 1;
	if (keycode == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int	on_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	if (keycode == 115)
		data->keys.s = 0;
	if (keycode == 100)
		data->keys.d = 0;
	if (keycode == 97)
		data->keys.a = 0;
	if (keycode == 65361)
		data->keys.left = 0;
	if (keycode == 65363)
		data->keys.right = 0;
	return (0);
}

int	control_input(t_data *data)
{
	double	movespeed = 0.03f;
	double	rotspeed = 0.01f;
	if (data->keys.w)
	{
		if(data->config.map_lines[(int)(data->posy)][(int)(data->posx + data->dirx * movespeed)] == '0')
			data->posx += data->dirx * movespeed;
		if(data->config.map_lines[(int)(data->posy + data->diry * movespeed)][(int)(data->posx)] == '0')
			data->posy += data->diry * movespeed;
	}
	if (data->keys.s)
	{
		if(data->config.map_lines[(int)(data->posy)][(int)(data->posx - data->dirx * movespeed)] == '0')
			data->posx -= data->dirx * movespeed;
		if(data->config.map_lines[(int)(data->posy - data->diry * movespeed)][(int)(data->posx)] == '0')
			data->posy -= data->diry * movespeed;
	}
	if (data->keys.d)
	{
		if(data->config.map_lines[(int)(data->posy)][(int)(data->posx + data->planex * movespeed)] == '0')
			data->posx += data->planex * movespeed;
		if(data->config.map_lines[(int)(data->posy + data->planey * movespeed)][(int)(data->posx)] == '0')
			data->posy += data->planey * movespeed;
	}
	if (data->keys.a)
	{
		if(data->config.map_lines[(int)(data->posy)][(int)(data->posx - data->planex * movespeed)] == '0')
			data->posx -= data->planex * movespeed;
		if(data->config.map_lines[(int)(data->posy - data->planey * movespeed)][(int)(data->posx)] == '0')
			data->posy -= data->planey * movespeed;
	}
	if (data->keys.left)
	{
		double olddirx = data->dirx;
		data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
		data->diry = olddirx * sin(rotspeed) + data->diry * cos(rotspeed);
		double oldplanex = data->planex;
		data->planex = data->planex * cos(rotspeed) - data->planey * sin(rotspeed);
		data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
	}
	if (data->keys.right)
	{
		double olddirx = data->dirx;
		data->dirx = data->dirx * cos(-rotspeed) - data->diry * sin(-rotspeed);
		data->diry = olddirx * sin(-rotspeed) + data->diry * cos(-rotspeed);
		double oldplanex = data->planex;
		data->planex = data->planex * cos(-rotspeed) - data->planey * sin(-rotspeed);
		data->planey = oldplanex * sin(-rotspeed) + data->planey * cos(-rotspeed);
	}
	render(data);
	return (0);
}
