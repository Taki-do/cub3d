/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:10:29 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/16 11:06:54 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_monsters(t_data *data)
{
	double	speed = 0.01;
	for (int i = 0; i < data->config.monster_count; i++)
	{
		t_monster *m = &data->config.monster[i];
		if (m->hp > 0)
		{
			double dx = data->posX - m->x;
			double dy = data->posY - m->y;
			double dist = sqrt(dx * dx + dy * dy);
			m->frame_timer++;
			if (m->frame_timer > 100)
			{
				m->frame = (m->frame + 1) % 2;
				m->frame_timer = 0;
			}
			if (dist > 1)
			{
				double vx = dx / dist;
				double vy = dy / dist;
				if (data->config.map_lines[(int)(m->y)][(int)(m->x + vx * speed)] == '0')
					m->x += vx * speed;
				if (data->config.map_lines[(int)(m->y + vy * speed)][(int)(m->x)] == '0')
					m->y += vy * speed;
			}
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
	if (keycode == 65307) // ESC
	{
		mlx_destroy_window(data->mlx, data->win);
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

int	control_input(t_data *data)
{
	double moveSpeed = 0.03f;
	double rotSpeed = 0.01f;
	if (data->keys.w)
	{
		if(data->config.map_lines[(int)(data->posY)][(int)(data->posX + data->dirX * moveSpeed)] == '0')
			data->posX += data->dirX * moveSpeed;
		if(data->config.map_lines[(int)(data->posY + data->dirY * moveSpeed)][(int)(data->posX)] == '0')
			data->posY += data->dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (data->keys.s)
	{
		if(data->config.map_lines[(int)(data->posY)][(int)(data->posX - data->dirX * moveSpeed)] == '0')
			data->posX -= data->dirX * moveSpeed;
		if(data->config.map_lines[(int)(data->posY - data->dirY * moveSpeed)][(int)(data->posX)] == '0')
			data->posY -= data->dirY * moveSpeed;
	}
	//move to the right
	if (data->keys.d)
	{
		if(data->config.map_lines[(int)(data->posY)][(int)(data->posX + data->planeX * moveSpeed)] == '0')
			data->posX += data->planeX * moveSpeed;
		if(data->config.map_lines[(int)(data->posY + data->planeY * moveSpeed)][(int)(data->posX)] == '0')
			data->posY += data->planeY * moveSpeed;
	}
	//move to the left
	if (data->keys.a)
	{
		if(data->config.map_lines[(int)(data->posY)][(int)(data->posX - data->planeX * moveSpeed)] == '0')
			data->posX -= data->planeX * moveSpeed;
		if(data->config.map_lines[(int)(data->posY - data->planeY * moveSpeed)][(int)(data->posX)] == '0')
			data->posY -= data->planeY * moveSpeed;
			
	}
	if (data->keys.left) //fleche gauche
	{
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
		data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
		data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
	}
	if (data->keys.right) //fleche droite
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
		data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
		data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
	}
	render(data);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x = -1;
	double 		rotSpeed = 0.03f;
	(void)y;

	if (last_x == 1)
		last_x = x;
	int delta_x = x - last_x;
	if (delta_x < 0) //fleche gauche
	{
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
		data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
		data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
	}
	if (delta_x > 0) //fleche droite
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-rotSpeed) - data->dirY * sin(-rotSpeed);
		data->dirY = oldDirX * sin(-rotSpeed) + data->dirY * cos(-rotSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-rotSpeed) - data->planeY * sin(-rotSpeed);
		data->planeY = oldPlaneX * sin(-rotSpeed) + data->planeY * cos(-rotSpeed);
	}
	last_x = x;
	render(data);
	return (0);
}
