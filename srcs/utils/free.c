/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:04:38 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 16:03:20 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
}

void	free_config(t_config *config)
{
	int	i;

	if (config->no_path)
		free(config->no_path);
	if (config->so_path)
		free(config->so_path);
	if (config->we_path)
		free(config->we_path);
	if (config->ea_path)
		free(config->ea_path);
	if (config->map_lines)
	{
		i = 0;
		while (config->map_lines[i])
			free(config->map_lines[i++]);
		free(config->map_lines);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->wall[i].img)
			mlx_destroy_image(data->mlx, data->wall[i].img);
		i++;
	}
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->monster_texture[0].img)
		mlx_destroy_image(data->mlx, data->monster_texture[0].img);
	if (data->monster_texture[1].img)
		mlx_destroy_image(data->mlx, data->monster_texture[1].img);
	if (data->monster_texture[2].img)
		mlx_destroy_image(data->mlx, data->monster_texture[2].img);
	if (data->shotgun[0].img)
		mlx_destroy_image(data->mlx, data->shotgun[0].img);
	if (data->shotgun[1].img)
		mlx_destroy_image(data->mlx, data->shotgun[1].img);
	if (data->shotgun[2].img)
		mlx_destroy_image(data->mlx, data->shotgun[2].img);
	if (data->door[0].img)
		mlx_destroy_image(data->mlx, data->door[0].img);
	if (data->door[1].img)
		mlx_destroy_image(data->mlx, data->door[1].img);
		
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
		
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (&data->config)
		free_config(&data->config);
	if (data->mlx)
		free(data->mlx);
	if (data->tab)
		free_char_tab(data->tab);
	if (data->dup)
	{
		printf("\n\nsegfault de ces morts\n\n");
		free_char_tab(data->dup);
	}
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}
