/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:12:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/12 13:25:08 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define WIDTH 600
# define HEIGHT 400

# define PI 3.14159

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	float 	posx;
	float 	posy;
	float	angle;
	float	pa;
	float	pdx;
	float	pdy;
}   t_data;

int		draw_player(t_data *data);
int		take_input(int keycode, t_data *data);

#endif