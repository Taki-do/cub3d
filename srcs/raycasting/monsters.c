/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:38:53 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/18 10:59:45 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_monster3(t_data *data, t_monster m, t_draw draw)
{
	int	y;

	y = -draw.spriteheight / 2 + HEIGHT / 2 - 1;
	while (++y < draw.spriteheight / 2 + HEIGHT / 2)
	{
		draw.d = y * 256 - HEIGHT * 128 + draw.spriteheight * 128;
		draw.texy = ((draw.d * 64) / draw.spriteheight) / 256;
		if (m.hp <= 0)
			draw.color = get_pixel(&data->monster_texture[2], draw.texx,
					draw.texy);
		else
			draw.color = get_pixel(&data->monster_texture[m.frame], draw.texx,
					draw.texy);
		if (draw.color != 0x000000)
			draw_pixel(&data->image, draw.stripe, y, draw.color);
	}
}

void	draw_monster2(t_data *data, t_monster m, t_draw draw)
{
	draw.stripe = -draw.spriteheight / 2 + draw.spritescreenx - 1;
	while (++draw.stripe < draw.spriteheight / 2 + draw.spritescreenx)
	{
		if (draw.transformy > 0 && draw.stripe >= 0 && draw.stripe < WIDTH
			&& draw.transformy < data->zbuffer[draw.stripe])
		{
			draw.texx = (draw.stripe - (-draw.spriteheight / 2
						+ draw.spritescreenx))
				* 64 / draw.spriteheight;
			if (draw.transformy > 0 && draw.stripe >= 0 && draw.stripe < WIDTH)
				draw_monster3(data, m, draw);
		}
	}
}

void	draw_monster(t_data *data, t_monster m)
{
	t_draw	draw;

	draw.invdet = 1.0 / (data->planex * data->diry
			- data->dirx * data->planey);
	draw.transformx = draw.invdet * (data->diry
			* (m.x - data->posx) - data->dirx * (m.y - data->posy));
	draw.transformy = draw.invdet * (-data->planey
			* (m.x - data->posx) + data->planex * (m.y - data->posy));
	draw.spritescreenx = (int)((WIDTH / 2)
			* (1 + draw.transformx / draw.transformy));
	draw.spriteheight = abs((int)(HEIGHT / draw.transformy));
	draw_monster2(data, m, draw);
}

void	check_zbuffer(t_data *data, t_monster *m, int transformx,
		int transformy)
{
	int	spritescreenx;
	int	tolerance;

	tolerance = 10;
	if (transformy <= 0)
		return ;
	spritescreenx = (int)((WIDTH / 2) * (1 + transformx / transformy));
	if (spritescreenx > WIDTH / 2 - tolerance
		&& spritescreenx < WIDTH / 2 + tolerance)
	{
		if (transformy < data->zbuffer[spritescreenx])
			m->hp -= 1;
	}
}

void	check_monster_hit(t_data *data)
{
	t_monster	*m;
	double		invdet;
	double		transformx;
	double		transformy;
	int			i;

	i = -1;
	while (++i < data->config.monster_count)
	{
		m = &data->config.monster[i];
		if (m->hp <= 0)
			return ;
		invdet = 1.0 / (data->planex * data->diry - data->dirx * data->planey);
		transformx = invdet * (data->diry
				* (m->x - data->posx) - data->dirx * (m->y - data->posy));
		transformy = invdet * (-data->planey
				* (m->x - data->posx) + data->planex * (m->y - data->posy));
		if (transformy <= 0)
			return ;
		check_zbuffer(data, m, transformx, transformy);
	}
}
