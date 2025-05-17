/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:47:46 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/17 15:05:20 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    update_door(t_data *data, t_door *d)
{
    
    double dX = d->x - data->posX;
	double dY = d->y - data->posY;
    double dist = sqrt(dX * dX + dY * dY);

    if (dist < 1.0)
        d->open = 1;
    else
        d->open = 0;
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
