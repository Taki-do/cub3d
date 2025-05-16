/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:38:53 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/16 18:11:36 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_monster(t_data *data, t_monster m)
{
	double spriteX = m.x - data->posX;
	double spriteY = m.y - data->posY;
	double invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY);
	double transformX = invDet * (data->dirY * spriteX - data->dirX * spriteY);
	double transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY);

	int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

	int spriteHeight = abs((int)(HEIGHT / transformY));
	int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
	int drawEndY = spriteHeight / 2 + HEIGHT / 2;

	int spriteWidth = spriteHeight; // carré
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	int drawEndX = spriteWidth / 2 + spriteScreenX;

	for (int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
        if (transformY > 0 && stripe >= 0 && stripe < WIDTH && transformY < data->zbuffer[stripe])
        {
            int texX = (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth;
    
            if (transformY > 0 && stripe >= 0 && stripe < WIDTH)
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
                    int texY = ((d * 64) / spriteHeight) / 256;
                    int color;
                    color = get_pixel(&data->monster_texture[m.frame], texX, texY);
                    //Ne pas dessiner transparent
                    if (color != 0x000000)
                        draw_pixel(&data->image, stripe, y, color);
                }
            }
        }
	}
}
