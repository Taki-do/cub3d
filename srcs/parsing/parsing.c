/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:11:53 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/12 17:17:29 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	**read_cub_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Map cannot be read", 2), NULL);
	while ((line = get_next_line(fd)))
	{
		tmp = ft_strjoin(content, line);
		free(content);
		content = tmp;
		free(line);
	}
	lines = ft_split(content, '\n');
	free(content);
	close (fd);
	return (lines);
}

int	check_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

void	parse_config(char **lines, t_config *config, int i, int elements_count)
{
	while (lines[i])
	{
		if (check_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		else if (check_element_line(lines[i]))
		{
			if (ft_strncmp(lines[i], "NO ", 3) == 0
				|| ft_strncmp(lines[i], "SO ", 3) == 0
				|| ft_strncmp(lines[i], "WE ", 3) == 0
				|| ft_strncmp(lines[i], "EA ", 3) == 0)
				parse_texture(lines[i++], config);
			else if (ft_strncmp(lines[i], "F ", 2) == 0
				|| ft_strncmp(lines[i], "C ", 2) == 0)
				parse_color_line(lines[i++], config);
			elements_count++;
		}
		else
			break ;
	}
	if (elements_count != 6)
		error_exit("Missing or duplicatre elements.");
	copy_map_lines(&lines[i], config, 0, 0);
}

void	copy_map_lines(char **map_start, t_config *config,
						int height, int max_width)
{
	int	i;
	int	len;

	while (map_start[height])
	{
		len = ft_strlen(map_start[height]);
		if (len > max_width)
			max_width = len;
		height++;
	}
	config->map_height = height;
	config->map_width = max_width;
	config->map_lines = ft_secure_malloc((height + 1) * sizeof(char *));
	i = 0;
	while (i < height)
	{
		config->map_lines[i] = ft_strdup(map_start[i]);
		i++;
	}
	config->map_lines[i] = NULL;
}