/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:06:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/14 17:54:07 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>

# define EMPTY '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define SPACE ' '

# define WIDTH 64 * 8
# define HEIGHT 64 * 8

# define MAP_SIZE 64

# define MAP_WIDTH 8
# define MAP_HEIGHT 8

# define PI 3.1415926535
# define FOV 60 * (PI / 180) // Conversion radiant

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

typedef struct s_texture
{
	void	*img;
	void	*addr;
	int		x;
	int		y;
	int		bpp;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	t_texture	wall_img;
	t_texture	image;
	float 		posx;
	float 		posy;
	float		pa;
	float		pdx;
	float		pdy;
    char        **map;
}   t_data;

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
/*                                 FLOOD FILL                                 */
/* ************************************************************************** */

void	flood_fill(char **map, int y, int x);
char	**dup_map(char **original);

/* ************************************************************************** */
/*                                     MAP                                    */
/* ************************************************************************** */
void	valid_char(char c);
int		is_player(char c);
void	check_surroundings(char **map,int y, int x);
void	validate_map(t_config *config, int x, int y, int player_found);

int		take_input(int keycode, t_data *data);
void	draw_3d(t_data *data);
int 	get_pixel(t_texture *texture, int x, int y);
void	draw_pixel(t_texture *texture, int x, int y, int color);
int     is_wall(t_data *data, int px, int py);

/* ************************************************************************** */
/*                               EXIT AND ERROR                               */
/* ************************************************************************** */
void	error_exit(char *msg);

/* ************************************************************************** */
/*                              MEMORY MANAGEMENT                             */
/* ************************************************************************** */
void	*ft_secure_malloc(size_t bytes);
void	free_char_tab(char **tab);
void	free_config(t_config *config);

/* ************************************************************************** */
/*                                CHAR HANDLING                               */
/* ************************************************************************** */
void	replace_tabs(char *line);

#endif