/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:59:45 by bael-bad          #+#    #+#             */
/*   Updated: 2025/12/07 16:48:45 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	draw_player_circle(t_game *game, int px, int py)
{
	int	size;
	int	x;
	int	y;

	size = 5;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			if (x * x + y * y <= size * size)
				my_mlx_pixel_put(&game->img, px + x, py + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_direction_line(t_game *game, int *px, int steps)
{
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;

	x_inc = (game->player.player_dir_x * 20) / (float)steps;
	y_inc = (game->player.player_dir_y * 20) / (float)steps;
	x = px[0];
	y = px[1];
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(&game->img, (int)x, (int)y, 0x00FF00);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

static void	draw_player_dir(t_game *game, int px, int py)
{
	int	line_end[2];
	int	d[2];
	int	steps;
	int	pos[2];

	line_end[0] = px + (int)(game->player.player_dir_x * 20);
	line_end[1] = py + (int)(game->player.player_dir_y * 20);
	d[0] = line_end[0] - px;
	d[1] = line_end[1] - py;
	steps = abs(d[0]);
	if (abs(d[1]) > steps)
		steps = abs(d[1]);
	pos[0] = px;
	pos[1] = py;
	if (steps > 0)
		draw_direction_line(game, pos, steps);
}

void	draw_player(t_game *game)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = (int)game->player.ply_x;
	pixel_y = (int)game->player.ply_y;
	draw_player_circle(game, pixel_x, pixel_y);
	draw_player_dir(game, pixel_x, pixel_y);
}
