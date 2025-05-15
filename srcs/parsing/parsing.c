/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:11:53 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/15 14:45:07 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	process_line(t_list **line_list, char *line, int *line_count)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	ft_lstadd_back(line_list, ft_lstnew(line));
	(*line_count)++;
}

char	**read_cub_map(const char *filename, int line_count, int i)
{
	int		fd;
	char	*line;
	char	**lines;
	t_list	*line_list;
	t_list	*current;

	line_list = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Map cannot be read", 2), NULL);
	line = get_next_line(fd);
	while (line)
	{
		process_line(&line_list, line, &line_count);
		line = get_next_line(fd);
	}
	lines = ft_secure_malloc((line_count + 1) * sizeof(char *));
	current = line_list;
	while (current)
	{
		lines[i++] = ft_strdup(current->content);
		current = current->next;
	}
	lines[i] = NULL;
	return (ft_lstclear(&line_list, free), close(fd), lines);
}

int	check_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

void	parse_config(char **lines, t_config *config, int i, int elements_count)
{
	while (lines[i])
	{
		if (has_tab(lines[i]))
			error_exit("Tab is not valid in config.");
		if (check_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		else if (check_element_line(lines[i]))
		{
			elements_count += process_element(lines[i], config);
			i++;
		}
		else
			break ;
	}
	if (elements_count != 6)
		error_exit("Missing or duplicate elements.");
	copy_map_lines(&lines[i], config, -1, 0);
}

void	copy_map_lines(char **map_start, t_config *config,
						int height, int max_width)
{
	int	i;
	int	len;
	int	empty_found;

	empty_found = 0;
	while (map_start[++height])
	{
		if (check_empty_line(map_start[height]))
			empty_found = 1;
		else if (empty_found)
			error_exit("empty line found inside the map.");
		len = ft_strlen(map_start[height]);
		if (len > max_width)
			max_width = len;
	}
	config->map_height = height;
	config->map_width = max_width;
	config->map_lines = ft_secure_malloc((height + 1) * sizeof(char *));
	i = -1;
	while (++i < height)
		config->map_lines[i] = ft_strdup(map_start[i]);
	config->map_lines[i] = NULL;
}
