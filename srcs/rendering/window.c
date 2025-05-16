/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:14:39 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/16 17:09:52 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_window(t_data *data, int width, int height)
{
	data->win = mlx_new_window(data->mlx, width, height, "cub3D");
	if (!data->win)
		error_exit("Failed to create window.");
	data->image.img = mlx_new_image(data->mlx, width, height);
	if (!data->image.img)
		error_exit("Failed to create image.");
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
							&data->image.line_len, &data->image.endian);
	if (!data->image.addr)
		error_exit("Failed to get image data.");
}
