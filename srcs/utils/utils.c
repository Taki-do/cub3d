/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:07:21 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/19 15:30:56 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"

void	*ft_secure_malloc(size_t bytes, t_data *data)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with malloc", data);
	return (ret);
}

void	error_exit(char *msg, t_data *data)
{
	free_data(data);
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