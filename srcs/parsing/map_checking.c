/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:40:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/20 14:07:15 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

void	valid_char(char c, t_data *data)
{
	if (c != EMPTY && c != WALL && c != NORTH && c != SOUTH
		&& c != EAST && c != WEST && c != SPACE && c != 'M' && c != 'D'
		&& c != '\r')
		error_exit("Invalid character in map.", data);
}

int	is_player(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

void	validate_map3(t_config *config, int x, int y)
{
	if (config->map_lines[y][x] == 'D')
	{
		config->door[config->door_count].x = x;
		config->door[config->door_count].y = y;
		config->door[config->door_count].frame = 0;
		config->door[config->door_count].open = 0;
		config->door_count++;
		if (config->door_count > 10)
			error_exit("Limit is set to 10 doors", config->data);
	}
}

void	validate_map2(t_config *config, int x, int y, int *player_found)
{
	if (is_player(config->map_lines[y][x]))
	{
		if (*player_found)
			error_exit("Multiple players found.", config->data);
		config->player_x = x;
		config->player_y = y;
		config->player_dir = config->map_lines[y][x];
		*player_found = 1;
		config->map_lines[y][x] = '0';
	}
	if (config->map_lines[y][x] == 'M')
	{
		config->monster[config->monster_count].x = x;
		config->monster[config->monster_count].y = y;
		config->monster[config->monster_count].frame = 0;
		config->monster[config->monster_count].hp = 1;
		config->monster_count++;
		if (config->monster_count > 50)
			error_exit("Limit is set to 50 monsters", config->data);
		config->map_lines[y][x] = '0';
	}
	validate_map3(config, x, y);
}

void	validate_map(t_config *config, int x, int y, int player_found)
{
	char	**map_copy;

	config->monster_count = 0;
	config->door_count = 0;
	while (config->map_lines[++y])
	{
		x = 0;
		while (config->map_lines[y][x])
		{
			valid_char(config->map_lines[y][x], config->data);
			validate_map2(config, x, y, &player_found);
			x++;
		}
	}
	if (!player_found)
		error_exit("No player found in the map.", config->data);
	map_copy = dup_map(config->map_lines, config->data);
	flood_fill(map_copy, config->player_y, config->player_x, config->data);
	config->data->dup = NULL;
	free_char_tab(map_copy);
}
