/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:30:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/12 17:59:45 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int main(int ac, char **av)
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
	if(!lines)
		error_exit("Failed to read .cub file");
	parse_config(lines, &config, 0, 0);
	validate_map(&config);
	printf("Yeaah, you know how to parse!\n");
	printf("Player at (%d,%d), facing %c\n", config.player_y, config.player_x, config.player_dir);
	i = 0;
	while (config.map_lines[i])
	{
		printf("%s\n", config.map_lines[i]);
		i++;
	}
	free_char_tab(lines);
	free_char_tab(config.map_lines);
	return (0);
}