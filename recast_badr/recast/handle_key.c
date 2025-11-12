/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:54:18 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/09 10:59:22 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.player_dir_x;
	old_plane_x = game->player.plane_x;
	game->player.player_dir_x = game->player.player_dir_x * cos(angle)
		- game->player.player_dir_y * sin(angle);
	game->player.player_dir_y = old_dir_x * sin(angle)
		+ game->player.player_dir_y * cos(angle);
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

static int	can_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / game->img.cell_size);
	map_y = (int)(y / game->img.cell_size);
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;
	double	old_x;
	double	old_y;

	old_x = game->player.ply_x;
	old_y = game->player.ply_y;
	new_x = old_x + dx;
	new_y = old_y + dy;
	if (can_move(game, new_x, old_y))
		game->player.ply_x = new_x;
	if (can_move(game, game->player.ply_x, new_y))
		game->player.ply_y = new_y;
}

int	handle_key(int keycode, t_game *game)
{
	double	move;

	move = game->player.move_speed * game->img.cell_size;
	if (keycode == 65307)
		exit(0);
	if (keycode == 'w')
		move_player(game, game->player.player_dir_x * move,
			game->player.player_dir_y * move);
	else if (keycode == 's')
		move_player(game, -game->player.player_dir_x * move,
			-game->player.player_dir_y * move);
	else if (keycode == 'a')
		move_player(game, -game->player.plane_x * move,
			-game->player.plane_y * move);
	else if (keycode == 'd')
		move_player(game, game->player.plane_x * move,
			game->player.plane_y * move);
	else if (keycode == 65361)
		rotate_player(game, -game->player.rot_speed);
	else if (keycode == 65363)
		rotate_player(game, game->player.rot_speed);
	return (0);
}
