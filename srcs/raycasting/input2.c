/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:48:10 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/20 09:48:10 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../includes/utils.h"

void	update_monsters2(t_data *data, t_monster *m, t_draw draw, double speed)
{
	double	vx;
	double	vy;

	if (draw.dist > 1)
	{
		vx = draw.dx / draw.dist;
		vy = draw.dy / draw.dist;
		if (data->config.map_lines[(int)(m->y)][(int)(m->x + vx * speed)]
			== '0')
			m->x += vx * speed;
		if (data->config.map_lines[(int)(m->y + vy * speed)][(int)(m->x)]
			== '0')
			m->y += vy * speed;
	}
}

void	update_monsters(t_data *data)
{
	int			i;
	double		speed;
	t_draw		draw;
	t_monster	*m;

	speed = 0.01;
	i = -1;
	while (++i < data->config.monster_count)
	{
		m = &data->config.monster[i];
		if (m->hp > 0)
		{
			draw.dx = data->posx - m->x;
			draw.dy = data->posy - m->y;
			draw.dist = sqrt(draw.dx * draw.dx + draw.dy * draw.dy);
			m->frame_timer++;
			if (m->frame_timer > 100)
			{
				m->frame = (m->frame + 1) % 2;
				m->frame_timer = 0;
			}
			update_monsters2(data, m, draw, speed);
		}
	}
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		shoot(data);
	return (0);
}

int	on_press(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	if (keycode == 115)
		data->keys.s = 1;
	if (keycode == 100)
		data->keys.d = 1;
	if (keycode == 97)
		data->keys.a = 1;
	if (keycode == 65361)
		data->keys.left = 1;
	if (keycode == 65363)
		data->keys.right = 1;
	if (keycode == 65307)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}

int	on_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	if (keycode == 115)
		data->keys.s = 0;
	if (keycode == 100)
		data->keys.d = 0;
	if (keycode == 97)
		data->keys.a = 0;
	if (keycode == 65361)
		data->keys.left = 0;
	if (keycode == 65363)
		data->keys.right = 0;
	return (0);
}
