/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:46 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/18 11:09:18 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    update_door(t_data *data, t_door *d)
{
    
    double dX = d->x - data->posX;
	double dY = d->y - data->posY;
    double dist = sqrt(dX * dX + dY * dY);

    if (dist < 2.0)
    {
        d->open = 1;
        data->config.map_lines[(int)d->y][(int)d->x] = '0';
    }
    else
    {
        d->open = 0;
        data->config.map_lines[(int)d->y][(int)d->x] = 'D';
    }
}
/*
1111
1001
11D1
10N1
1111

door   x = 2 y = 2;
player x = 2 y = 3;
*/
