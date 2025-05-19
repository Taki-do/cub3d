/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:46 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 11:03:22 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	door_is_open(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.door_count)
	{
		if (data->config.door[data->config.door_count].open == 1)
			return (1);
		i++;
	}
	return (0);
}

void	update_door(t_data *data)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;
	t_door	*d;

	i = -1;
	while (++i < data->config.door_count)
	{
		d = &data->config.door[i];
		dx = d->x - data->posx;
		dy = d->y - data->posy;
		dist = sqrt(dx * dx + dy * dy);
		if (dist < 2.0)
		{
			d->open = 1;
			data->config.map_lines[(int)d->y][(int)d->x] = '0';
		}
		else
		{
			d->open = 0;
			data->config.map_lines[(int)d->y][(int)d->x] = 'D';
		}
	}
}
