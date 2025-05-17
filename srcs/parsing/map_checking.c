/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:40:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/17 10:06:15 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

void	valid_char(char c)
{
	if (c != EMPTY && c != WALL && c != NORTH && c != SOUTH
		&& c != EAST && c != WEST && c != SPACE && c != 'M')
		error_exit("Invalid character in map.");
}

int	is_player(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

int	is_monster(char c)
{
	return (c == 'M');
}

void	validate_map(t_config *config, int x, int y, int player_found)
{
	char	**map_copy;

	config->monster_count = 0;
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
			if (is_monster(config->map_lines[y][x]))
			{
				config->monster[config->monster_count].x = x;
				config->monster[config->monster_count].y = y;
				config->monster[config->monster_count].frame = 0;
				config->monster[config->monster_count].hp = 1;
				config->monster_count++;
				config->map_lines[y][x] = '0';
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
