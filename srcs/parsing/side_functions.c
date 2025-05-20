/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:35:39 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 15:50:54 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/utils.h"

void	char_check_rgb(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\t')
			error_exit("Tab is not valid in RGB range.", data);
		if (!ft_isdigit(str[i]) && str[i] != 'F'
			&& str[i] != 'C' && str[i] != ' ' && str[i] != ','
			&& str[i] != '\r')
			error_exit("Invalid caracter in floor/ceiling lines.", data);
	}
}

int	process_element(char *line, t_config *config)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(line, config);
	else if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		parse_color_line(line, config);
	else
		return (0);
	return (1);
}
