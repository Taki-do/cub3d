/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:19:43 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/19 12:35:49 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_window(t_texture *texture) //opti possible avec memset
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			draw_pixel(texture, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int	render(t_data *data)
{
	int	x = 0;
	clear_window(&data->image);
	while (x < WIDTH)
	{
		data->CameraX = 2 * x / (double)WIDTH - 1; //par de gauche (-1) jusqu'a droite au fur et a mesure
		data->rayDirX = data->dirX + data->planeX * data->CameraX; //calcul des vecteur qui donne la coordonne qui commence a gauche
		data->rayDirY = data->dirY + data->planeY * data->CameraX; //le FOV aussi avec 0.66 qui donne la distance de vue (ex: -1, -0.66)
		data->mapX = (int)data->posX;
		data->mapY = (int)data->posY;
		//chiffre enorme pour dire qu'on ne peut pas passer en X ou en Y dans le cas ou l'on va que en X ou en Y
		if (data->rayDirX == 0)
			data->deltaDistX = 1e30;
		else
			data->deltaDistX = fabs(1 / data->rayDirX);
		if (data->rayDirY == 0)
			data->deltaDistY = 1e30;
		else
			data->deltaDistY = fabs(1 / data->rayDirY);
		data->hit = 0;
		//on regarde dans quelle direction va le rayon stepX et stepY, on calcul les side dist pour savoir le prochain mur en X ou Y
		if (data->rayDirX < 0)
		{
			data->stepX = -1;
			data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;
		}
		else
		{
			data->stepX = 1;
			data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
		}
		if (data->rayDirY < 0)
		{
			data->stepY = -1;
			data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
		}
		else
		{
			data->stepY = 1;
			data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
		}
		//DDA start
		//on va en X ou Y suivant le plus proche et on decale nos mesure en fonction pour preparer le prochain passage
		while (data->hit == 0)
		{
			if (data->sideDistX < data->sideDistY)
			{
				data->sideDistX += data->deltaDistX;
				data->mapX += data->stepX;
				data->side = 0; //North or South hit
			}
			else
			{
				data->sideDistY += data->deltaDistY;
				data->mapY += data->stepY;
				data->side = 1; //Ouest ou est
			}
			if ((data->config.map_lines[data->mapY][data->mapX] == '1') ||
				(data->config.map_lines[data->mapY][data->mapX] == 'D'))
				{
					if (data->config.map_lines[data->mapY][data->mapX] == 'D' &&
						door_is_open(data))
						data->hit = 0;
					else
						data->hit = 1;
				}
		}
		//un recule un coup car quand on touche on est dans le mur mais on veut la distance avant le mur
		//aussi on utilise la distance qui part du camera plan pour eviter le fish eye effect
		if (data->side == 0)
			data->prepWallDist = data->sideDistX - data->deltaDistX;
		else
			data->prepWallDist = data->sideDistY - data->deltaDistY;

		data->zbuffer[x] = data->prepWallDist; // enregistre la position du mur a chaque colonne (bonus)
		
		//on calcule la hauteur de la ligne
		data->lineHeight = (int)(HEIGHT / data->prepWallDist);
		//le debut et la fin de la ligne verticale
		data->drawStart = -data->lineHeight / 2 + HEIGHT / 2;
		if (data->drawStart < 0)
			data->drawStart = 0; //securite pour pas sortie de l'ecran
		data->drawEnd = data->lineHeight / 2 + HEIGHT /2;
		if (data->drawEnd >= HEIGHT)
			data->drawEnd = HEIGHT - 1; //securite pour pas sortie de l'ecran
		double wallX; //where exactly the wall was hit
		if (data->side == 0)
			wallX = data->posY + data->prepWallDist * data->rayDirY;
		else
			wallX = data->posX + data->prepWallDist * data->rayDirX;
		wallX -= floor((wallX));
		int texture_nb;
		
		if (data->side == 0)
		{
			if (data->rayDirX > 0)
				texture_nb = 0;
			else
				texture_nb = 1;
		}
		else
		{
			if (data->rayDirY > 0)
				texture_nb = 2;
			else
				texture_nb = 3;
		}
		//x coordinate on the texture
		int texX = (int)(wallX * (double)64);
		if(data->side == 0 && data->rayDirX > 0)
			texX = 64 - texX - 1;
		if(data->side == 1 && data->rayDirY < 0)
			texX = 64 - texX - 1;
		int i = 0;
		while (i < data->drawStart)
		{
			draw_pixel(&data->image, x, i, data->config.ceiling_color);
			i++;
		}
		i = data->drawStart; //suppr
		while (i < data->drawEnd)
		{
			int d = i * 256 - HEIGHT * 128 + data->lineHeight * 128;
			int tex_y = ((d * 64) / data->lineHeight) / 256;
			if (data->side == 1)
				tex_y /= 2; //brightness
			if (data->config.map_lines[data->mapY][data->mapX] == 'D' &&
						door_is_open(data))
				draw_pixel(&data->image, x, i, get_pixel(&data->door[1], texX, tex_y));
			else if (data->config.map_lines[data->mapY][data->mapX] == 'D' &&
						!door_is_open(data))
				draw_pixel(&data->image, x, i, get_pixel(&data->door[0], texX, tex_y));
			else
				draw_pixel(&data->image, x, i, get_pixel(&data->wall[texture_nb], texX, tex_y));
			i++;
		}
		i = data->drawEnd;
		while (i < HEIGHT)
		{
			draw_pixel(&data->image, x, i, data->config.floor_color);
			i++;
		}
		x++;
	}
	for (int i = 0; i < data->config.monster_count; i++)
		draw_monster(data, data->config.monster[i]);
	update_door(data);
	update_monsters(data);
	update_gun(data);
	draw_gun(data, 3);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	draw_minimap(data);
	return (0);
}
