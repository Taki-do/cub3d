/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:26:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/14 15:25:39 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../includes/raycasting.h"

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	int height = 64;
	int width = 64;
	data.image.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bpp, &data.image.line_len, &data.image.endian);
	data.wall_img.img = mlx_xpm_file_to_image(data.mlx, "wall_bricks_old_64.xpm", &width, &height);
	data.wall_img.addr = mlx_get_data_addr(data.wall_img.img, &data.wall_img.bpp, &data.wall_img.line_len, &data.wall_img.endian);

	data.posx = WIDTH / 2;
	data.posy = HEIGHT / 2;
	data.pa = 0;
	data.pdx = cos(data.pa);
	data.pdy = sin(data.pa);
	
	draw_3d(&data);
	mlx_key_hook(data.win, take_input, &data);
	mlx_loop(data.mlx);
}
*/