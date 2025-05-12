/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:40:58 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/12 18:20:34 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	valid_char(char c)
{
	if (c != EMPTY && c != WALL && c != NORTH && c != SOUTH
		&& c != EAST && c != WEST && c != SPACE)
		error_exit("Inalid character in map.");
}

int	is_player(char c)
{
	return (c == NORTH || c == SOUTH || c == EAST || c == WEST);
}

static char	get_map_char(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (' ');
	if (!map[y])
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (' ');
	return (map[y][x]);
}

void	check_surroundings(char **map,int y, int x)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = get_map_char(map, y - 1, x);
	down = get_map_char(map, y + 1, x);
	left = get_map_char(map, y, x - 1);
	right = get_map_char(map, y, x + 1);
	if (up == ' ' || down == ' ' || left == ' ' || right == ' '
		|| up == '\t' || down == '\t' || left == '\t' || right == '\t')
		error_exit("Map not closed: space around open tile");
	if (up == '\0' || down == '\0' || left == '\0' || right == '\0')
		error_exit("Map not closed: out-of-bounds near open tile");
}

void	validate_map(t_config *config)
{
	char	**map;
	int		x;
	int		y;
	int		player_found;

	map = config->map_lines;
	y = 0;
	player_found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			valid_char(map[y][x]);
			if (map[y][x] == EMPTY || is_player(map[y][x]))
				check_surroundings(map, y, x);
			if (is_player(map[y][x]))
			{
				if (player_found)
					error_exit("Multiple players found.");
				player_found = 1;
				config->player_y = y;
				config->player_x = x;
				config->player_dir = map[y][x];
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		error_exit("No player found in the map.");
}
