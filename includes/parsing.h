/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:13:28 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/20 13:57:00 by taomalbe         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                    FILE                                    */
/* ************************************************************************** */
int		check_cub_extension(char *filename);
int		check_xpm_extension(char *filename);
char	**read_cub_map(const char *filename, int line_count,
			int i, t_data *data);
int		check_empty_line(char *line);
void	parse_config(char **lines, t_config *config, int i, int elements_count);
void	copy_map_lines(char **map_start, t_config *config, int height,
			int max_width);

/* ************************************************************************** */
/*                                  ELEMENTS                                  */
/* ************************************************************************** */
int		check_element_line(char *line);
void	parse_texture(char *line, t_config *config);
int		combine_rgb(int r, int g, int b);
void	parse_color_line(char *line, t_config *config);

/* ************************************************************************** */
/*                                 FLOOD FILL                                 */
/* ************************************************************************** */

void	flood_fill(char **map, int y, int x, t_data *data);
char	**dup_map(char **original, t_data *data);

/* ************************************************************************** */
/*                                     MAP                                    */
/* ************************************************************************** */
//void	valid_char(char c);
int		is_player(char c);
//void	check_surroundings(char **map,int y, int x);
void	validate_map(t_config *config, int x, int y, int player_found);

/* ************************************************************************** */
/*                               SIDE FUNCTIONS                               */
/* ************************************************************************** */
void	char_check_rgb(char *str, t_data *data);
int		process_element(char *line, t_config *config);

#endif