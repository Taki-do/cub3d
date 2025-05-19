/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:19:43 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 16:11:57 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	configure_drawing(t_data *data, int x)
{
	if (data->side == 0)
		data->prepwalldist = data->sidedistx - data->deltadistx;
	else
		data->prepwalldist = data->sidedisty - data->deltadisty;
	data->zbuffer[x] = data->prepwalldist;
	data->lineheight = (int)(HEIGHT / data->prepwalldist);
	data->drawstart = -data->lineheight / 2 + HEIGHT / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineheight / 2 + HEIGHT / 2;
	if (data->drawend >= HEIGHT)
		data->drawend = HEIGHT - 1;
	if (data->side == 0)
		data->wallX = data->posy + data->prepwalldist * data->raydiry;
	else
		data->wallX = data->posx + data->prepwalldist * data->raydirx;
	data->wallX -= floor((data->wallX));
}

int	choose_texture(t_data *data)
{
	int	nb;

	if (data->side == 0)
	{
		if (data->raydirx > 0)
			nb = 0;
		else
			nb = 1;
	}
	else
	{
		if (data->raydiry > 0)
			nb = 2;
		else
			nb = 3;
	}
	data->texx = (int)(data->wallX * (double)64);
	if (data->side == 0 && data->raydirx > 0)
		data->texx = 64 - data->texx - 1;
	if (data->side == 1 && data->raydiry < 0)
		data->texx = 64 - data->texx - 1;
	return (nb);
}

void	draw_end_buffer(t_data *data, int i, int x)
{
	i = data->drawend - 1;
	while (++i < HEIGHT)
		draw_pixel(&data->image, x, i, data->config.floor_color);
}

void	draw_buffer(t_data *data, int x, int i, int texture_nb)
{
	int	d;
	int	tex_y;

	while (++i < data->drawstart)
		draw_pixel(&data->image, x, i, data->config.ceiling_color);
	i = data->drawstart - 1;
	while (++i < data->drawend)
	{
		d = i * 256 - HEIGHT * 128 + data->lineheight * 128;
		tex_y = ((d * 64) / data->lineheight) / 256;
		if (data->side == 1)
			tex_y /= 2;
		if (data->config.map_lines[data->mapy][data->mapx] == 'D' &&
					door_is_open(data))
			draw_pixel(&data->image, x, i,
				get_pixel(&data->door[1], data->texx, tex_y));
		else if (data->config.map_lines[data->mapy][data->mapx] == 'D' &&
					!door_is_open(data))
			draw_pixel(&data->image, x, i,
				get_pixel(&data->door[0], data->texx, tex_y));
		else
			draw_pixel(&data->image, x, i,
				get_pixel(&data->wall[texture_nb], data->texx, tex_y));
	}
	draw_end_buffer(data, i, x);
}

int	render(t_data *data)
{
	int	x;
	int	i;

	clear_window(&data->image);
	x = 0;
	i = -1;
	while (x < WIDTH)
	{
		init_dda(data, x);
		while (data->hit == 0)
			dda_loop(data);
		configure_drawing(data, x);
		draw_buffer(data, x, i, choose_texture(data));
		x++;
	}
	while (++i < data->config.monster_count)
		draw_monster(data, data->config.monster[i]);
	update_door(data);
	update_monsters(data);
	update_gun(data);
	draw_gun(data, 3);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	draw_minimap(data);
	return (0);
}
