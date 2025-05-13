/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:52:19 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 17:05:50 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "cub3d.h"
# include "config.h"
# include "structs.h"

/* ************************************************************************** */
/*                                 TEXTURING                                  */
/* ************************************************************************** */
void	load_texture(void *mlx, char *path, t_img *tex);
void	load_all_textures(t_data *data);
void	draw_background(t_data *data, int width, int height);

/* ************************************************************************** */
/*                                   WINDOW                                   */
/* ************************************************************************** */
void	init_window(t_data *data, int width, int height);

#endif