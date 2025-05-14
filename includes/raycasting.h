/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:12:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/14 15:15:10 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define WIDTH 64 * 8
# define HEIGHT 64 * 8

# define MAP_SIZE 64

# define MAP_WIDTH 8
# define MAP_HEIGHT 8

# define PI 3.1415926535
# define FOV 60 * (PI / 180) // Conversion radiant

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
}   t_data;

int		take_input(int keycode, t_data *data);
void	draw_3d(t_data *data);
int get_pixel(t_texture *texture, int x, int y);
void	draw_pixel(t_texture *texture, int x, int y, int color);
void cast_horizontal(t_data *data, float ra, int *hx, int *hy, float *h_dist);
void cast_vertical(t_data *data, float ra, int *vx, int *vy, float *v_dist);
int is_wall(int px, int py);

#endif