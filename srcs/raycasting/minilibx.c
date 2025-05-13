/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:14:52 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/13 15:56:44 by taomalbe         ###   ########.fr       */
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
	int		num_rays; //nombre de rayon
	float	step_angle; //donne la distance qui separe les rayons
	float	ra; //angle de rotation
	int		rx;
	int		ry;
	int		r;
	int		i;
	int		y;
	float	dist;
	int line_height;
	int draw_start;
	int draw_end;

	mlx_clear_window(data->mlx, data->win);
	
	num_rays = WIDTH / 8;
	step_angle = FOV / num_rays;
	r = 0;
	while (r++ < num_rays)
	{
		ra = data->pa - (FOV / 2) + r * step_angle; //angle de gauche a droite 
		// Reste dans le cercle trigo
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		// Ray stepping
		i = 0;
		while (i++ < 1000)
		{
			// defini la position x et y du rayon dans un plan 2D
			rx = data->posx + i * cos(ra);
			ry = data->posy + i * sin(ra);
			if (is_wall(rx, ry))
			{
				dist = i; // Ajuste la vrai distance, + c'est court en distance + le mur va paraitre grand
				dist = dist * cos(ra - data->pa); // Calcul hauteur du mur (proche = grand, loin = petit)
				line_height = (MAP_SIZE * HEIGHT) / dist;
				draw_start = (HEIGHT / 2) - (line_height / 2);
				draw_end = (HEIGHT / 2) + (line_height / 2);
				y = draw_start;
				while (y++ < draw_end)
					mlx_pixel_put(data->mlx, data->win, r * 8, y, 0xFF0000);
				break;
			}
		}
	}
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