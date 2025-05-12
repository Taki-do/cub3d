/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:13:28 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/12 11:21:43 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_config
{
	char	*no_path;
	char	*so_patch;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**map_lines;
}	t_config;

#endif