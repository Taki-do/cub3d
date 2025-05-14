/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:04:38 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 09:53:17 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_char_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
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
