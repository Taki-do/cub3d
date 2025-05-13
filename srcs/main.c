/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:30:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 17:19:24 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	char **lines;
	t_data	data;
	
	if (ac != 2)
		error_exit("Usage: ./cub3D map.cub");
	if (!check_cub_extension(av[1]))
		error_exit("Map file has to be .cub format");
	init_data(&data);
	lines = read_cub_map(av[1]);
	if (!lines)
	{
		free_data(&data);
		error_exit("Failed to read .cub file");
	}
	parse_config(lines, &data.config, 0, 0);
	validate_map(&data.config, 0, -1, 0);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		free_data(&data);
		error_exit("Failed to init MLX");
	}
	load_all_textures(&data);
	init_window(&data, WIN_WIDTH, WIN_HEIGHT);
	draw_background(&data, WIN_WIDTH, WIN_HEIGHT);
	mlx_put_image_to_window(data.mlx, data.win, data.screen.img, 0, 0);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.win, 17, 0, exit_game, &data);
	mlx_loop(data.mlx);
	free_char_tab(lines);
	free_data(&data);
	return (0);
}
