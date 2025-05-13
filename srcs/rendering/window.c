/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:14:39 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 13:28:45 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mlx_utils.h"

void	init_window(t_data *data, int width, int height)
{
	data->win = mlx_new_window(data->mlx, width, height, "cub3d");
	if (!data->win)
		error_exit("Failed to create window.");
	data->screen.img = mlx_new_image(data->mlx, width, height);
	if (!data->screen.img)
		error_exit("Failed to create image.");
	data->screen.addr = mlx_get_data_addr(data->screen.img, &data->screen.bpp,
							&data->screen.line_len, &data->screen.endian);
	if (!data->screen.addr)
		error_exit("Failed to get image data.");
}
