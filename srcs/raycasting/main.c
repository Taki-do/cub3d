/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:26:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/12 13:32:08 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int	main(void)
{
	t_data	data;

	data.posx = WIDTH /2;
	data.posy = HEIGHT / 2;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	draw_player(&data);
	mlx_hook(data.win, 02, 1L << 0, take_input, &data);
	mlx_loop(data.mlx);
}