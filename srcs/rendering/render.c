/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:02:50 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/18 11:10:25 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_utils.h"

void	load_texture(void *mlx, char *path, t_texture *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit("Failed to load texture.");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		error_exit("Failed to get texture data.");
}

void	load_all_textures(t_data *data)
{
	load_texture(data->mlx, data->config.no_path, &data->wall[0]);
	load_texture(data->mlx, data->config.so_path, &data->wall[1]);
	load_texture(data->mlx, data->config.we_path, &data->wall[2]);
	load_texture(data->mlx, data->config.ea_path, &data->wall[3]);
	load_texture(data->mlx, "Cacodemons.xpm", &data->monster_texture[0]);
	load_texture(data->mlx, "Cacodemons_shoot.xpm", &data->monster_texture[1]);
	load_texture(data->mlx, "Cacodemons_dead.xpm", &data->monster_texture[2]);
	load_texture(data->mlx, "shotgun_frame1.xpm", &data->shotgun[0]);
	load_texture(data->mlx, "shotgun_frame2.xpm", &data->shotgun[1]);
	load_texture(data->mlx, "shotgun_frame3.xpm", &data->shotgun[2]);
	load_texture(data->mlx, "door.xpm", &data->door[0]);
	load_texture(data->mlx, "door_open.xpm", &data->door[1]);
}
