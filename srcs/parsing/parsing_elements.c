/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:19:01 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 15:33:01 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

int	check_element_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

void	parse_texture(char *line, t_config *config)
{
	int		i;
	char	**tokens;

	i = -1;
	while (line[++i])
	{
		if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]) && line[i] != '.'
			&& line[i] != '/' && line[i] != ' ' && line[i] != '_'
			&& line[i] != '\r')
			error_exit("Invalid character in texture line.", config->data);
	}
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		error_exit("Invalid texture format. Should be: xxxx.xpm", config->data);
	if (ft_strncmp(tokens[0], "NO", 2) == 0)
		config->no_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "SO", 2) == 0)
		config->so_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "WE", 2) == 0)
		config->we_path = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "EA", 2) == 0)
		config->ea_path = ft_strdup(tokens[1]);
	else
		error_exit("Can only be : NO, SO, WE and EA", config->data);
	free_char_tab(tokens);
}

int	parse_rgb_component(char *s, t_data *data)
{
	int	value;

	value = ft_atoi(s);
	if (value < 0 || value > 255)
		error_exit("RGB color out of range, should be between 0 and 255", data);
	return (value);
}

int	combine_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	parse_color_line(char *line, t_config *config)
{
	char	**tokens;
	char	**rgb;
	int		r;
	int		g;
	int		b;

	char_check_rgb(line, config->data);
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		error_exit("Invalide color format, should be: X n,n,n", config->data);
	rgb = ft_split(tokens[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Invalide RGB format, should be: n,n,n", config->data);
	r = parse_rgb_component(rgb[0], config->data);
	g = parse_rgb_component(rgb[1], config->data);
	b = parse_rgb_component(rgb[2], config->data);
	if (ft_strcmp(tokens[0], "F") == 0)
		config->floor_color = combine_rgb(r, g, b);
	else if (ft_strcmp(tokens[0], "C") == 0)
		config->ceiling_color = combine_rgb(r, g, b);
	else
		error_exit("Unknown color. Can only be: F or C", config->data);
	free_char_tab(tokens);
	free_char_tab(rgb);
}
