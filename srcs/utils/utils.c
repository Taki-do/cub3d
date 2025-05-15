/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:07:21 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/15 14:37:00 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_secure_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with malloc");
	return (ret);
}

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
}

int	has_tab(char *str)
{
	int	i;
	
	i = -1;
	while(str[++i])
	{
		if (str[i] == '\t')
			return (1);
	}
	return (0);
}