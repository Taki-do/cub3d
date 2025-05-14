/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:21:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 11:31:58 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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

void	flood_fill(char **map, int y, int x)
{
	char	c;

	c = get_map_char(map, y, x);
	if (c == ' ' || c == '\0' || c == '\t')
		error_exit("Map not closed: open area detected");
	if (c == '1' || c == 'x')
		return ;
	if (c != '0' && !is_player(c))
		error_exit("Invalid character inside map during flood fill");
	map[y][x] = 'x';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
}

char	**dup_map(char **original)
{
	int		i;
	char	**copy;

	i = 0;
	while (original[i])
		i++;
	copy = ft_secure_malloc((i + 1) * sizeof(char *));
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
