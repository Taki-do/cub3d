/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:14:52 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/12 13:31:36 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

void	mlx_free(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

int	draw_player(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_pixel_put(data->mlx, data->win, data->posx + 1, data->posy, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx - 1, data->posy, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx, data->posy + 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx, data->posy - 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx + 1, data->posy + 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx - 1, data->posy - 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx - 1, data->posy + 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx + 1, data->posy - 1, 0x00FF0000);
	mlx_pixel_put(data->mlx, data->win, data->posx, data->posy, 0x00FF0000);
	return (0);
}



int	take_input(int keycode, t_data *data)
{
	if (keycode == 119) //W
	{
		data->posy--;
		data->posx += data->pdx;
		data->posy += data->pdy;

	}
	else if (keycode == 97) //A
	{
		data->posx--;
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (keycode == 115) //S
	{
		data->posy++;
		data->posx -= data->pdx;
		data->posy -= data->pdy;
	}
	else if (keycode == 100) //D
	{
		data->posx++;
		data->pa += 0.1;
		if (data->pa > 0)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (keycode == 65307)
	{
		mlx_free(data);
		exit(0);
	}
	return (draw_player(data));
}