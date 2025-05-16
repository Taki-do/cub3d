/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:30:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/15 14:17:15 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/utils.h"
#include "../includes/mlx_utils.h"

int	main(int ac, char **av)
{
	char **lines;
	t_data	data;
	
	if (ac != 2)
		error_exit("Usage: ./cub3D map.cub");
	if (!check_cub_extension(av[1]))
		error_exit("Map file has to be .cub format");
	init_data(&data);
	lines = read_cub_map(av[1], 0, 0);
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
	init_keys(&data);
	init_position(&data, data.config.player_dir);
	data.posX = data.config.player_x;
	data.posY = data.config.player_y;
	init_window(&data, WIDTH, HEIGHT);
	render(&data);
	mlx_loop_hook(data.mlx, control_input, &data);
	mlx_hook(data.win, 2, 1L<<0, on_press, &data);
	mlx_hook(data.win, 3, 1L<<1, on_release, &data);
	mlx_hook(data.win, 6, 1L<<6, mouse_move, &data);
	mlx_loop(data.mlx);
	free_char_tab(lines);
	free_data(&data);
	return (0);
}
