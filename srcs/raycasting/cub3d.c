/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:19:43 by taomalbe          #+#    #+#             */
/*   Updated: 2025/05/16 11:45:45 by taomalbe         ###   ########.fr       */
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
		//assign really big number to avoid problems
		if (data->rayDirX == 0)
			data->deltaDistX = 1e30;
		else
			data->deltaDistX = fabs(1 / data->rayDirX);
		if (data->rayDirY == 0)
			data->deltaDistY = 1e30;
		else
			data->deltaDistY = fabs(1 / data->rayDirY);
		data->hit = 0;
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
			if (data->config.map_lines[data->mapY][data->mapX] == '1') // !! Change needed here
				data->hit = 1;
		}
		//un recule un coup car quand on touche on est dans le mur mais on veut la distance avant le mur
		//aussi on utilise la distance qui part du camera plan pour eviter le fish eye effect
		if (data->side == 0)
			data->prepWallDist = data->sideDistX - data->deltaDistX;
		else
			data->prepWallDist = data->sideDistY - data->deltaDistY;
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
			draw_pixel(&data->image, x, i, get_pixel(&data->wall[texture_nb], texX, tex_y));
			i++;
		}
		i = data->drawEnd;
		while (i < HEIGHT)
		{
			draw_pixel(&data->image, x, i, data->config.floor_color);
			i++;
		}
		//avoid frame part
		//move forward if no wall in front of you
		
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

/*
int main(void)
{
	t_data	data;
	init_keys(&data);
	int	width = 64;
	int	height = 64;
	
	init_position(&data, 'O');
	data.posX = 22;
	data.posY = 12;
	
	//double	time = 0; //current frame
	//double	oldTime = 0; //previous frame

	//init mlx
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	data.image.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bpp, &data.image.line_len, &data.image.endian);

	data.wall[0].img = mlx_xpm_file_to_image(data.mlx, "doom_wall.xpm", &width, &height);
	data.wall[0].addr = mlx_get_data_addr(data.wall[0].img, &data.wall[0].bpp, &data.wall[0].line_len, &data.wall[0].endian);
	data.wall[1].img = mlx_xpm_file_to_image(data.mlx, "doom_wall2.xpm", &width, &height);
	data.wall[1].addr = mlx_get_data_addr(data.wall[1].img, &data.wall[1].bpp, &data.wall[1].line_len, &data.wall[1].endian);
	data.wall[2].img = mlx_xpm_file_to_image(data.mlx, "doom_wall3.xpm", &width, &height);
	data.wall[2].addr = mlx_get_data_addr(data.wall[2].img, &data.wall[2].bpp, &data.wall[2].line_len, &data.wall[2].endian);
	data.wall[3].img = mlx_xpm_file_to_image(data.mlx, "doom_wall4.xpm", &width, &height);
	data.wall[3].addr = mlx_get_data_addr(data.wall[3].img, &data.wall[3].bpp, &data.wall[3].line_len, &data.wall[3].endian);

	render(&data);
	mlx_loop_hook(data.mlx, control_input, &data);
	mlx_hook(data.win, 2, 1L<<0, on_press, &data);
	mlx_hook(data.win, 3, 1L<<1, on_release, &data);
	mlx_loop(data.mlx);
}
*/