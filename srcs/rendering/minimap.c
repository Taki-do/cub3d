/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:01:46 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 16:15:34 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    draw_square(t_texture *texture, int x, int y, int color)
{
    int        i;
    int        j;
    int        size;

    size = 15;
    j = -1;
    while (++j < size)
    {
        i = -1;
        while (++i < size)
            draw_pixel(texture, x * size + i, y * size + j, color);
    }
}

int    get_tile_color(char c)
{
    if (c == '1' || c == ' ')
        return (0x888888);
    if (c == '0')
        return (0x000000);
    if (c == 'D')
        return (0xFFD700);
    return (0x333333);
}

void    draw_minimap(t_data *data)
{
    int    map_x;
    int    map_y;
    int    x;
    int    y;
    int    color;

    y = -6;
    while (++y <= 5)
    {
        x = -6;
        while (++x <= 5)
        {
            map_x = (int)data->posX + x;
            map_y = (int)data->posY + y;
            if (map_y >= 0 && map_y < data->config.map_height
                && map_x >= 0
                && map_x < (int)ft_strlen(data->config.map_lines[map_y]))
            {
                color = get_tile_color(data->config.map_lines[map_y][map_x]);
                draw_square(&data->image, x + 6, y + 6, color);
            }
        }
    }
    draw_square(&data->image, 6, 6, 0xFF0000);
}