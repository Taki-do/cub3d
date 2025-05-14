/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:19:01 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 11:43:53 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		error_exit("Invalid texture line format. Should be: XX xxxx.xpm");
	if (ft_strcmp(tokens[0], "NO") == 0)
		config->no_path = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "SO") == 0)
		config->so_path = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "WE") == 0)
		config->we_path = ft_strdup(tokens[1]);
	else if (ft_strcmp(tokens[0], "EA") == 0)
		config->ea_path = ft_strdup(tokens[1]);
	else
		error_exit("Unknown texture identifier."
			"Can only be : NO, SO, WE and EA");
	free_char_tab(tokens);
}

int	parse_rgb_component(char *s)
{
	int	value;

	value = ft_atoi(s);
	if (value < 0 || value > 255)
		error_exit("RGB color out of range, should be between 0 and 255");
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

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		error_exit("Invalide color line format, should be: X n,n,n");
	rgb = ft_split(tokens[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Invalide RGB format, should be: n,n,n");
	r = parse_rgb_component(rgb[0]);
	g = parse_rgb_component(rgb[1]);
	b = parse_rgb_component(rgb[2]);
	if (ft_strcmp(tokens[0], "F") == 0)
		config->floor_color = combine_rgb(r, g, b);
	else if (ft_strcmp(tokens[0], "C") == 0)
		config->ceiling_color = combine_rgb(r, g, b);
	else
		error_exit("Unknown color identifier. Can only be: F or C");
	free_char_tab(tokens);
	free_char_tab(rgb);
}
