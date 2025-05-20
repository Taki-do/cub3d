/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:07:09 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/20 13:50:15 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

void	init_position_w(t_data *data)
{
	data->dirx = 1;
	data->diry = 0;
	data->planex = 0;
	data->planey = -0.66;
}

void	init_position(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = -0.66;
		data->planey = 0;
	}
	else if (dir == 'S')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = 0.66;
		data->planey = 0;
	}
	else if (dir == 'E')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = 0.66;
	}
	else if (dir == 'W')
		init_position_w(data);
}
