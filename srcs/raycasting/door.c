/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:46 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/18 11:47:19 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int door_is_open(t_data *data)
{
    int i;

    i = 0;
    while (i < data->config.door_count)
    {
        if (data->config.door[data->config.door_count].open == 1)
            return (1);
        i++;
    }
    return (0);
}

void    update_door(t_data *data)
{
    int i;
    double dX;
	double dY;
    double dist;
    t_door  *d;

    i = 0;
    while (i < data->config.door_count)
    {

        d = &data->config.door[i];
        dX = d->x - data->posX;
	    dY = d->y - data->posY;
        dist = sqrt(dX * dX + dY * dY);
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
        i++;
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
