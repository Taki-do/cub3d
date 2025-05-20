/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:50:53 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/20 10:50:53 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mouse_move2(double rotspeed, t_data *data, int delta_x)
{
	double	olddirx;
	double	oldplanex;

	if (delta_x < 0)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(rotspeed) - data->diry * sin(rotspeed);
		data->diry = olddirx * sin(rotspeed) + data->diry * cos(rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex
			* cos(rotspeed) - data->planey * sin(rotspeed);
		data->planey = oldplanex * sin(rotspeed) + data->planey * cos(rotspeed);
	}
	if (delta_x > 0)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-rotspeed) - data->diry * sin(-rotspeed);
		data->diry = olddirx * sin(-rotspeed) + data->diry * cos(-rotspeed);
		oldplanex = data->planex;
		data->planex = data->planex
			* cos(-rotspeed) - data->planey * sin(-rotspeed);
		data->planey = oldplanex
			* sin(-rotspeed) + data->planey * cos(-rotspeed);
	}
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x;
	double		rotspeed;
	int			delta_x;

	(void)y;
	rotspeed = 0.03f;
	delta_x = x - last_x;
	mouse_move2(rotspeed, data, delta_x);
	last_x = x;
	render(data);
	return (0);
}
