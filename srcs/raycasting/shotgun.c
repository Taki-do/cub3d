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

int shoot(t_data *data)
{
    data->shotgun_frame = 1;
    data->shotgun_frame_timer = 30;
	check_monster_hit(data);
    return (0);
}

void update_gun(t_data *data)
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


void draw_gun(t_data *data, int scale)
{
	t_texture *tex = &data->shotgun[data->shotgun_frame];
	int tex_w = tex->width;
	int tex_h = tex->height;

	int screen_w = tex_w * scale;
	int screen_h = tex_h * scale;

	int x_start = (WIDTH - screen_w) / 2;
	int y_start;
    if (data->shotgun_frame == 0)
        y_start = HEIGHT - screen_h + 50;
	else
		y_start = HEIGHT - screen_h;
	for (int y = 0; y < screen_h; y++)
	{
		for (int x = 0; x < screen_w; x++)
		{
			int src_x = x / scale;
			int src_y = y / scale;

			int color = get_pixel(tex, src_x, src_y);
			if (color != 0x000000)
				draw_pixel(&data->image, x + x_start, y + y_start, color);
		}
	}
}

