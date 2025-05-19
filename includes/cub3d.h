/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:20:02 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 14:07:09 by tboulogn         ###   ########.fr       */
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

# define WIDTH 600
# define HEIGHT 480
# define FLOOR_COLOR 0x333333
# define CELLING_COLOR 0x87CEEB

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

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	t_texture	wall[4];
	t_texture	image;
	t_keys		keys;
	t_config	config;
	int			**tab_int;
	void		*mlx;
	void		*win;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		prepwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
}	t_data;

//[textures.c]
int		get_pixel(t_texture *texture, int x, int y);
void	draw_pixel(t_texture *texture, int x, int y, int color);

//[cub3d.c]
int		render(t_data *data);

//[raycasting/init.c]
void	init_keys(t_data *data);
void	init_position(t_data *data, char dir);

//[raycasting/input.c]
int		control_input(t_data *data);
int		on_release(int keycode, t_data *data);
int		on_press(int keycode, t_data *data);

//[utils/utils.c]
void	error_exit(char *msg);

#endif