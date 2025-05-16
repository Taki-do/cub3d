/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:20:02 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/16 11:32:37 by taomalbe         ###   ########.fr       */
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
typedef struct s_monster
{
	double 	x;
	double 	y;
	int		frame;
	int		frame_timer;
}	t_monster;

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
    t_texture   wall[4];
    t_texture   image;
	t_texture	monster_texture[2];
	t_texture	shotgun[3];
	int			shotgun_frame;
	int			shotgun_frame_timer;
    t_keys      keys;
	t_config	config;
	int			**tab_int;
    void    *mlx;
    void    *win;
    double	posX;
    double  posY;
	double	dirX;
    double  dirY;
	double	planeX;
    double  planeY;
    double CameraX;
	double rayDirX;
	double rayDirY;
	//dans quel carre de la map somme nous
	int		mapX;
	int		mapY;
	//taille du rayon de notre position jusqu'a la bordure du prochain carre
	double sideDistX;
    double sideDistY;
	//taille du rayon du carre actuel jusqu'a la bordure du prochain carre
	double deltaDistX;
	double deltaDistY;
	double prepWallDist; //to calculate lenght of the ray
	//la distance a faire pour passer au prochain carre
	int		stepX;
	int		stepY;
	int		hit; //un mur a ete touche ?
	int		side; //c'etait au N S ou E W ?
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		last_mouse_x;
	int		ignore_next_mouse;
	double	zbuffer[WIDTH];
}   t_data;

//[textures.c]
int     get_pixel(t_texture *texture, int x, int y);
void	draw_pixel(t_texture *texture, int x, int y, int color);

//[cub3d.c]
int	render(t_data *data);

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

//[utils/utils.c]
void	error_exit(char *msg);

//[raycasting/monster.c]
void draw_monster(t_data *data, t_monster m);

//[raycasting/shotgun.c]
int	 shoot(t_data *data);
void update_gun(t_data *data);
void draw_gun(t_data *data, int scale);

#endif