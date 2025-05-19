/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:21:55 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 15:47:16 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

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

void	flood_fill(char **map, int y, int x, t_data *data)
{
	char	c;

	c = get_map_char(map, y, x);
	if (c == ' ' || c == '\0' || c == '\t')
		error_exit("Map not closed: open area detected", data);
	if (c == '1' || c == 'x')
		return ;
	if (c != '0' && !is_player(c) && c != 'D')
		error_exit("Invalid character inside map during flood fill", data);
	map[y][x] = 'x';
	flood_fill(map, y + 1, x, data);
	flood_fill(map, y - 1, x, data);
	flood_fill(map, y, x + 1, data);
	flood_fill(map, y, x - 1, data);
}

char	**dup_map(char **original, t_data *data)
{
	int		i;
	char	**copy;

	i = 0;
	while (original[i])
		i++;
	copy = ft_secure_malloc((i + 1) * sizeof(char *), data);
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		i++;
	}
	copy[i] = NULL;
	data->dup = copy;
	return (copy);
}
