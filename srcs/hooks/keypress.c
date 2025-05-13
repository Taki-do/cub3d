/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:24:11 by tboulogn          #+#    #+#             */
/*   Updated: 2025/05/13 16:47:04 by tboulogn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hook.h"

int	exit_game(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit_game(data);
	return (0);
}