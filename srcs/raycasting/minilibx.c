/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:14:52 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/14 15:13:29 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	mlx_free(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};

int is_wall(int px, int py)
{
	int mx = px / MAP_SIZE;
	int my = py / MAP_SIZE;

	if (mx < 0 || mx >= MAP_WIDTH || my < 0 || my >= MAP_HEIGHT)
		return (1);
	return (map[my][mx]);
}

void	draw_3d(t_data *data)
{
	int	num_rays;
	int	hx;
	int	hy;
	int	rx;
	int	ry;
	int	r;
	int	i;
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	tex_width;
	int	tex_height;
	int	tex_x;
	float	step_angle;
	float	h_dist;
	float	dist;
	float	wall_hit_x;
	float	ra;

	num_rays = WIDTH;
	r = 0;
	tex_height = 64;
	tex_width = 64;
	step_angle = FOV / (float)num_rays;
	mlx_clear_window(data->mlx, data->win);
	while (r < num_rays)
	{
		ra = data->pa - (FOV / 2) + r * step_angle;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;

		hx = data->posx;
		hy = data->posy;
		h_dist = 0;
		i = 0;
		while (i < 1000)
		{
			rx = data->posx + i * cos(ra);
			ry = data->posy + i * sin(ra);
			if (is_wall(rx, ry))
			{
				hx = rx;
				hy = ry;
				h_dist = i;
				break;
			}
			i++;
		}

		dist = h_dist * cos(ra - data->pa);
		line_height = (MAP_SIZE * HEIGHT) / dist;
		draw_start = (HEIGHT / 2) - (line_height / 2);
		draw_end = (HEIGHT / 2) + (line_height / 2);
		
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end > HEIGHT)
			draw_end = HEIGHT;

		if (ra > PI / 2 && ra < 3 * PI / 2)
			wall_hit_x = fmodf(hx, MAP_SIZE);
		else
			wall_hit_x = fmodf(hy, MAP_SIZE);

		tex_x = (int)(wall_hit_x * tex_width / MAP_SIZE);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex_width)
			tex_x = tex_width - 1;

		i = 0;
		while (i < draw_start)
		{
			draw_pixel(&data->image, r, i, 0x87CEEB);
			i++;
		}
		
		i = draw_start;
		while (i < draw_end)
		{
			int d = i * 256 - HEIGHT * 128 + line_height * 128;
			int tex_y = ((d * tex_height) / line_height) / 256;

			draw_pixel(&data->image, r, i, get_pixel(&data->wall_img, tex_x, tex_y));
			i++;
		}
		
		i = draw_end;
		while (i < HEIGHT)
		{
			draw_pixel(&data->image, r, i, 0x333333);
			i++;
		}
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
}

int	take_input(int keycode, t_data *data)
{
	if (keycode == 119) // W
	{
		data->posx += data->pdx;
		data->posy += data->pdy;
	}
	else if (keycode == 115) // S
	{
		data->posx -= data->pdx;
		data->posy -= data->pdy;
	}
	else if (keycode == 97) // A
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (keycode == 100) // D
	{
		data->pa += 0.1;
		if (data->pa > 2 * PI)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (keycode == 65307) // ESC
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	draw_3d(data);
	return (0);
}
