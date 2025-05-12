/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:13:28 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/12 17:05:20 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define EMPTY '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define SPACE ' '

# include "cub3d.h"
# include "utils.h"

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**map_lines;
	int		map_height;
	int		map_width;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;


/* ************************************************************************** */
/*                                    FILE                                    */
/* ************************************************************************** */
int		check_cub_extension(char *filename);
char	**read_cub_map(const char *filename);
int		check_empty_line(char *line);
void	parse_config(char **lines, t_config *config, int i, int elements_count);
void	copy_map_lines(char **map_start, t_config *config, int height, int max_width);

/* ************************************************************************** */
/*                                  ELEMENTS                                  */
/* ************************************************************************** */
int		check_element_line(char *line);
void	parse_texture(char *line, t_config *config);
int		parse_rgb_component(char *s);
int		combine_rgb(int r, int g, int b);
void	parse_color_line(char *line, t_config *config);

/* ************************************************************************** */
/*                                     MAP                                    */
/* ************************************************************************** */
void	valid_char(char c);
int		is_player(char c);
void	check_surroundings(char **map,int y, int x);
void	validate_map(t_config *config, int x, int y, int player_found);

#endif