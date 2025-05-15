/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:24:11 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/14 16:29:06 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hook.h"

int	exit_game(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	take_input(int keycode, t_data *data)
{
	if (keycode == KEY_W)
	{
		data->posx += data->pdx;
		data->posy += data->pdy;
	}
	else if (keycode == KEY_S)
	{
		data->posx -= data->pdx;
		data->posy -= data->pdy;
	}
	else if (keycode == KEY_A)
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (keycode == KEY_D)
	{
		data->pa += 0.1;
		if (data->pa > 2 * PI)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
	}
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}
