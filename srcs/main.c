/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:30:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 16:03:54 by taomalbe         ###   ########.fr       */
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
		error_exit("Usage: ./cub3D map.cub", &data);
	if (!check_cub_extension(av[1]))
		error_exit("Map file has to be .cub format", &data);
	init_data(&data);
	data.config.data = &data;
	lines = read_cub_map(av[1], 0, 0, &data);
	data.tab = lines;
	if (!lines)
		error_exit("Failed to read .cub file", &data);
	parse_config(lines, &data.config, 0, 0);
	validate_map(&data.config, 0, -1, 0);
	data.mlx = mlx_init();
	if (!data.mlx)
		error_exit("Failed to init MLX", &data);
	
	load_all_textures(&data); //ICI
	init_keys(&data);
	init_position(&data, data.config.player_dir);
	data.posx = data.config.player_x;
	data.posy = data.config.player_y;
	init_window(&data, WIDTH, HEIGHT);
	render(&data);
	mlx_loop_hook(data.mlx, control_input, &data);
	mlx_hook(data.win, 2, 1L<<0, on_press, &data);
	mlx_hook(data.win, 3, 1L<<1, on_release, &data);
	mlx_hook(data.win, 6, 1L<<6, mouse_move, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_mouse_hook(data.win, mouse_press, &data);
	mlx_loop(data.mlx);
	free_char_tab(lines);
	free_data(&data);
	return (0);
}
