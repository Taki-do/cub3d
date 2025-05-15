/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:49 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/15 12:05:34 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "config.h"

typedef struct s_texture
{
	void	*img;
	void	*addr;
	int		x;
	int		y;
	int		bpp;
	int		width;
	int		height;
	int		endian;
	int		line_len;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	t_texture	texture[4];
	t_texture	screen;
	t_config	config;
	float		posx;
	float		posy;
	float		pa;
	float		pdx;
	float		pdy;
}	t_data;

#endif