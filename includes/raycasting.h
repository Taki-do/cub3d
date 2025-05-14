/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:12:16 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/14 11:35:08 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define WIDTH 64 * 8
# define HEIGHT 64 * 8

# define MAP_SIZE 64

# define PI 3.1415926535
# define FOV 60 * (PI / 180) // Conversion radiant

void	draw_3d(t_data *data);
int		get_pixel(t_texture texture, int x, int y);
void	draw_pixel(t_texture texture, int x, int y, int color);

#endif