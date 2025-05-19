/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:02:50 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 15:56:58 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_utils.h"
#include "../../includes/utils.h"



void	load_texture(void *mlx, char *path, t_texture *tex, t_data *data)
{
	path = ft_strtrim(path, "\r");
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(path);
		error_exit("Failed to load texture.", data);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		free(path);
		error_exit("Failed to get texture data.", data);
	}
	free(path);
}

void	load_all_textures(t_data *data)
{
	load_texture(data->mlx, data->config.no_path, &data->wall[0], data);
	load_texture(data->mlx, data->config.so_path, &data->wall[1], data);
	load_texture(data->mlx, data->config.we_path, &data->wall[2], data);
	load_texture(data->mlx, data->config.ea_path, &data->wall[3], data);
	load_texture(data->mlx, "textures/Cacodemons.xpm", &data->monster_texture[0], data);
	load_texture(data->mlx, "textures/Cacodemons_shoot.xpm", &data->monster_texture[1], data);
	load_texture(data->mlx, "textures/Cacodemons_dead.xpm", &data->monster_texture[2], data);
	load_texture(data->mlx, "textures/shotgun_frame1.xpm", &data->shotgun[0], data);
	load_texture(data->mlx, "textures/shotgun_frame2.xpm", &data->shotgun[1], data);
	load_texture(data->mlx, "textures/shotgun_frame3.xpm", &data->shotgun[2], data);
	load_texture(data->mlx, "textures/door.xpm", &data->door[0], data);
	load_texture(data->mlx, "textures/door_open.xpm", &data->door[1], data);
}
