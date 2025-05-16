/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:02:50 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/16 17:59:50 by taomalbe         ###   ########.fr       */
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
}

void	draw_background(t_data *data, int width, int height)
{
	int		y;
	int		x;
	int		color_floor;
	int		color_ceiling;
	int		color;
	char	*dst;

	color_floor = data->config.floor_color;
	color_ceiling = data->config.ceiling_color;
	y = -1;
	while (++y < height)
	{
		x = 0;
		if (y < height / 2)
			color = color_ceiling;
		else
			color = color_floor;
		while (x < width)
		{
			dst = data->image.addr + (y *data->image.line_len
				+ x * (data->image.bpp / 8));
			*(unsigned int *)dst = color;
			x++;
		}
	}
}
