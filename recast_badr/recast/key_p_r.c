/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_p_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:46:09 by bael-bad          #+#    #+#             */
/*   Updated: 2025/12/07 17:04:54 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	key_press(int keycode, t_game *game)
{
	game->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	game->key[keycode] = 0;
	return (0);
}
