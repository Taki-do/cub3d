/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:40:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 11:29:14 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	valid_char(char c)
{
	if (c != EMPTY && c != WALL && c != NORTH && c != SOUTH
		&& c != EAST && c != WEST && c != SPACE)
		error_exit("Invalid character in map.");
}

int	is_player(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

void	validate_map(t_config *config, int x, int y, int player_found)
{
	char	**map_copy;

	while (config->map_lines[++y])
	{
		x = 0;
		while (config->map_lines[y][x])
		{
			valid_char(config->map_lines[y][x]);
			if (is_player(config->map_lines[y][x]))
			{
				if (player_found)
					error_exit("Multiple players found.");
				config->player_x = x;
				config->player_y = y;
				config->player_dir = config->map_lines[y][x];
				player_found = 1;
			}
			x++;
		}
	}
	if (!player_found)
		error_exit("No player found in the map.");
	map_copy = dup_map(config->map_lines);
	flood_fill(map_copy, config->player_y, config->player_x);
	free_char_tab(map_copy);
}
