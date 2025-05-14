/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:30:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/14 18:23:44 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	char		**lines;
	t_config	config;
	int			i;

	if (ac != 2)
		error_exit("Usage; ./cube3d <file.cub>");
	if (!check_cub_extension(av[1]))
		error_exit("Map file has to be .cub format");
	ft_bzero(&config, sizeof(t_config));
	lines = read_cub_map(av[1]);
	if (!lines)
		error_exit("Failed to read .cub file");
	parse_config(lines, &config, 0, 0);
	validate_map(&config, 0, -1, 0);
	printf("Yeaah, you know how to parse!\n");
	printf("Player at (%d,%d), facing %c\n", config.player_y, config.player_x, config.player_dir);
	t_data	data;
	i = 0;
	data.map_size = 0;
	while (config.map_lines[i])
	{
		printf("%s\n", config.map_lines[i]);
		data.map_size += ft_strlen(config.map_lines[i]);
		i++;
	}
	data.map = config.map_lines;
	printf("data.map_size = %d\n", data.map_size);
	data.map_height = config.map_height;
	data.map_width = config.map_width;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	int height = 64;
	int width = 64;
	data.image.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bpp, &data.image.line_len, &data.image.endian);
	data.wall_img.img = mlx_xpm_file_to_image(data.mlx, "doom_wall.xpm", &width, &height);
	data.wall_img.addr = mlx_get_data_addr(data.wall_img.img, &data.wall_img.bpp, &data.wall_img.line_len, &data.wall_img.endian);

	data.posx = WIDTH / 2;
	data.posy = HEIGHT / 2;
	data.pa = 0;
	data.pdx = cos(data.pa);
	data.pdy = sin(data.pa);
	draw_3d(&data);
	mlx_key_hook(data.win, take_input, &data);
	mlx_loop(data.mlx);
	free_char_tab(lines);
	free_config(&config);
	return (0);
}
