/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:02:50 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 13:12:06 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_utils.h"

void	load_texture(void *mlx, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit("Failed to load texture.");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->img)
		error_exit("Failed to get texture data.");
}

void	load_all_textures(t_data *data)
{
	load_texture(data->mlx, data->config.no_path, &data->texture[0]);
	load_texture(data->mlx, data->config.so_path, &data->texture[1]);
	load_texture(data->mlx, data->config.we_path, &data->texture[2]);
	load_texture(data->mlx, data->config.ea_path, &data->texture[3]);
}