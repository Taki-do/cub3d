/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:01:46 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:26 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_square(t_texture *texture, int x, int y, int color)
{
	int		i;
	int		j;
	int		size;

	size = 15;

	j = -1;
	while(++j < size)
	{
		i = -1;
		while (++i < size)
			draw_pixel(texture, x * size + i, y * size + j, color);
	}
}

void	draw_minimap(t_data *data)
{
	int	map_x;
	int	map_y;
	int	x;
	int	y;
	int	color;

	y = -6;
	while (++y <= 5)
	{
		x = -6;
		while (++x <= 5)
		{
			map_x = (int)data->posX + x;
			map_y = (int)data->posY + y;
			if (map_x >= 0 && map_y >= 0 && map_x < data->config.map_width && map_y < data->config.map_height)
			{
				if (data->config.map_lines[map_y][map_x] == '1')
					color = 0x888888;
				else if (data->config.map_lines[map_y][map_x] == '0')
					color = 0x000000;
				else if (data->config.map_lines[map_y][map_x] == 'D')
					color = 0xFFD700;
				draw_square(&data->image, x + 6, y + 6, color);
			}
		}
	}
	draw_square(&data->image, 6, 6, 0xFF0000);
}
