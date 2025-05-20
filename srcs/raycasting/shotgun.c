/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shotgun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:45:14 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/17 10:06:51 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	shoot(t_data *data)
{
	data->shotgun_frame = 1;
	data->shotgun_frame_timer = 30;
	check_monster_hit(data);
	return (0);
}

void	update_gun(t_data *data)
{
	if (data->shotgun_frame > 0)
	{
		data->shotgun_frame_timer--;
		if (data->shotgun_frame_timer <= 0)
		{
			data->shotgun_frame++;
			if (data->shotgun_frame > 2)
				data->shotgun_frame = 0;
			else
				data->shotgun_frame_timer = 3;
		}
	}
}

void	draw_gun2(int scale, int screen_h, int screen_w, t_data *data)
{
	int			x;
	int			y;
	int			color;
	int			y_start;
	t_texture	*tex;

	tex = &data->shotgun[data->shotgun_frame];
	if (data->shotgun_frame == 0)
		y_start = HEIGHT - screen_h + 50;
	else
		y_start = HEIGHT - screen_h;
	y = -1;
	while (++y < screen_h)
	{
		x = -1;
		while (++x < screen_w)
		{
			color = get_pixel(tex, x / scale, y / scale);
			if (color != 0x000000)
				draw_pixel(&data->image, x + (WIDTH - screen_w) / 2,
					y + y_start, color);
		}
	}
}

void	draw_gun(t_data *data, int scale)
{
	t_texture	*tex;
	int			screen_w;
	int			screen_h;

	tex = &data->shotgun[data->shotgun_frame];
	screen_w = tex->width * scale;
	screen_h = tex->height * scale;
	draw_gun2(scale, screen_h, screen_w, data);
}
