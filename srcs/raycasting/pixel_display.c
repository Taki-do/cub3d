/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:26:36 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/13 15:38:13 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

int get_pixel(t_texture texture, int x, int y)
{
    char *pixel;

    pixel = texture.addr + (y * texture.line_len + x * (texture.bpp / 8));
    return (*(unsigned int *)pixel);
}

void	draw_pixel(t_texture texture, int x, int y, int color)
{
	char *dst = texture.addr + (y * texture.line_len + x * (texture.bpp / 8));
	*(unsigned int *)dst = color;
}