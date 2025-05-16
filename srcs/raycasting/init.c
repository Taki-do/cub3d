/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:07:09 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/15 19:07:36 by taomalbe         ###   ########.fr       */
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

void	init_position(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (dir == 'S')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
	else if (dir == 'E')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	else if (dir == 'W')
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
}