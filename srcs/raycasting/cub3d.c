/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:19:43 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 14:21:34 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_window(t_texture *texture)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			draw_pixel(texture, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int	render(t_data *data)
{
	int	x = 0;
	clear_window(&data->image);
	while (x < WIDTH)
	{
		data->camerax = 2 * x / (double)WIDTH - 1;
		data->raydirx = data->dirx + data->planex * data->camerax;
		data->raydiry = data->diry + data->planey * data->camerax;
		data->mapx = (int)data->posx;
		data->mapy = (int)data->posy;
		if (data->raydirx == 0)
			data->deltadistx = 1e30;
		else
			data->deltadistx = fabs(1 / data->raydirx);
		if (data->raydiry == 0)
			data->deltadisty = 1e30;
		else
			data->deltadisty = fabs(1 / data->raydiry);
		data->hit = 0;
		if (data->raydirx < 0)
		{
			data->stepx = -1;
			data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
		}
		else
		{
			data->stepx = 1;
			data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
		}
		if (data->raydiry < 0)
		{
			data->stepy = -1;
			data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
		}
		else
		{
			data->stepy = 1;
			data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
		}
		while (data->hit == 0)
		{
			if (data->sidedistx < data->sidedisty)
			{
				data->sidedistx += data->deltadistx;
				data->mapx += data->stepx;
				data->side = 0;
			}
			else
			{
				data->sidedisty += data->deltadisty;
				data->mapy += data->stepy;
				data->side = 1;
			}
			if (data->config.map_lines[data->mapy][data->mapx] == '1')
				data->hit = 1;
		}
		if (data->side == 0)
			data->prepwalldist = data->sidedistx - data->deltadistx;
		else
			data->prepwalldist = data->sidedisty - data->deltadisty;
		data->lineheight = (int)(HEIGHT / data->prepwalldist);
		data->drawstart = -data->lineheight / 2 + HEIGHT / 2;
		if (data->drawstart < 0)
			data->drawstart = 0;
		data->drawend = data->lineheight / 2 + HEIGHT /2;
		if (data->drawend >= HEIGHT)
			data->drawend = HEIGHT - 1;
		double wallx;
		if (data->side == 0)
			wallx = data->posy + data->prepwalldist * data->raydiry;
		else
			wallx = data->posx + data->prepwalldist * data->raydirx;
		wallx -= floor((wallx));
		int texture_nb;
		
		if (data->side == 0)
		{
			if (data->raydirx > 0)
				texture_nb = 0;
			else
				texture_nb = 1;
		}
		else
		{
			if (data->raydiry > 0)
				texture_nb = 2;
			else
				texture_nb = 3;
		}
		int texx = (int)(wallx * (double)64);
		if(data->side == 0 && data->raydirx > 0)
			texx = 64 - texx - 1;
		if(data->side == 1 && data->raydiry < 0)
			texx = 64 - texx - 1;
		int i = 0;
		while (i < data->drawstart)
		{
			draw_pixel(&data->image, x, i, data->config.ceiling_color);
			i++;
		}
		i = data->drawstart;
		while (i < data->drawend)
		{
			int d = i * 256 - HEIGHT * 128 + data->lineheight * 128;
			int tex_y = ((d * 64) / data->lineheight) / 256;
			if (data->side == 1)
				tex_y /= 2;
			draw_pixel(&data->image, x, i, get_pixel(&data->wall[texture_nb], texx, tex_y));
			i++;
		}
		i = data->drawend;
		while (i < HEIGHT)
		{
			draw_pixel(&data->image, x, i, data->config.floor_color);
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}
