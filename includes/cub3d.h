/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:20:02 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 15:47:00 by taomalbe         ###   ########.fr       */
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

//[BONUS]

typedef struct s_door
{
	double 	x;
	double 	y;
	int		frame;
	int		open;
}	t_door;

typedef struct s_monster
{
	double 	x;
	double 	y;
	int		hp;
	int		frame;
	int		frame_timer;
}	t_monster;

struct s_data;

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
	int		monster_count;
	int		door_count;
	struct s_data		*data;
	t_door		door[10];
	t_monster	monster[50];
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
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

typedef struct s_data
{
	t_texture	wall[4];
	t_texture	image;
	t_texture	monster_texture[3];
	t_texture	shotgun[3];
	t_texture	door[2];
	t_config	config;
    t_keys      keys;
	int			shotgun_frame;
	int			shotgun_frame_timer;
	char		**tab;
	char		**dup;
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
	double		wallX;
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
	int			texx;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			last_mouse_x;
	int			ignore_next_mouse;
	double		zbuffer[WIDTH];
}   t_data;

//[textures.c]
int     get_pixel(t_texture *texture, int x, int y);
void	draw_pixel(t_texture *texture, int x, int y, int color);

//[raycasting/cub3d.c]
int		render(t_data *data);
void	clear_window(t_texture *texture);

//[raycasting/init.c]
void	init_keys(t_data *data);
void	init_position(t_data *data, char dir);

//[raycasting/input.c]
int	control_input(t_data *data);
int	on_release(int keycode, t_data *data);
int	on_press(int keycode, t_data *data);
int	mouse_move(int x, int y, t_data *data);
int	mouse_press(int button, int x, int y, t_data *data);

void	update_monsters(t_data *data);

//[raycasting/monster.c]
void draw_monster(t_data *data, t_monster m);
void check_monster_hit(t_data *data);

//[raycasting/shotgun.c]
int	 shoot(t_data *data);
void update_gun(t_data *data);
void draw_gun(t_data *data, int scale);

//[raycasting/door.c]
void    update_door(t_data *data);
int door_is_open(t_data *data);

//[rendering/minimap.c]
void	draw_minimap(t_data *data);

//[raycasting/dda.c]
void	init_step(t_data *data);
void	init_dda(t_data *data, int x);
void	dda_loop(t_data *data);

#endif