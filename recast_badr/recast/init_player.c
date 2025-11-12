/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:55:11 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/09 10:55:28 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	set_dir_ns(t_game *game)
{
	if (game->player.player_dir == 'N')
	{
		game->player.player_dir_x = 0.0;
		game->player.player_dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->player.player_dir == 'S')
	{
		game->player.player_dir_x = 0.0;
		game->player.player_dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

static void	set_dir_ew(t_game *game)
{
	if (game->player.player_dir == 'E')
	{
		game->player.player_dir_x = 1.0;
		game->player.player_dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (game->player.player_dir == 'W')
	{
		game->player.player_dir_x = -1.0;
		game->player.player_dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->img.cell_size = 32;
	game->player.ply_x = (game->player_x * game->img.cell_size)
		+ (game->img.cell_size / 2.0);
	game->player.ply_y = (game->player_y * game->img.cell_size)
		+ (game->img.cell_size / 2.0);
	game->player.move_speed = 0.1;
	game->player.rot_speed = 0.05;
	game->player.player_dir = game->player_dir_char;
	set_dir_ns(game);
	set_dir_ew(game);
}
