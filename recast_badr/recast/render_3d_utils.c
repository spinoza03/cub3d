/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:46:45 by bael-bad          #+#    #+#             */
/*   Updated: 2025/12/07 16:53:15 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	calc_step_dist(t_game *game, double *pos, double *side_dist)
{
	if (game->camera.raydirx < 0)
	{
		game->camera.stepx = -1;
		side_dist[0] = (pos[0] - game->camera.mapx) * \
			game->camera.delta_dist_x;
	}
	else
	{
		game->camera.stepx = 1;
		side_dist[0] = (game->camera.mapx + 1.0 - pos[0]) * \
			game->camera.delta_dist_x;
	}
	if (game->camera.raydiry < 0)
	{
		game->camera.stepy = -1;
		side_dist[1] = (pos[1] - game->camera.mapy) * \
			game->camera.delta_dist_y;
	}
	else
	{
		game->camera.stepy = 1;
		side_dist[1] = (game->camera.mapy + 1.0 - pos[1]) * \
			game->camera.delta_dist_y;
	}
}

static void	check_hit(t_game *game)
{
	if (game->camera.mapy >= 0 && game->camera.mapx >= 0 && \
		game->camera.mapy < game->map_height && \
		game->camera.mapx < game->map_width)
	{
		if (game->map[game->camera.mapy][game->camera.mapx] == '1')
			game->camera.hit = 1;
	}
	else
		game->camera.hit = 1;
}

static void	perform_dda(t_game *game, double *side_dist)
{
	game->camera.hit = 0;
	while (game->camera.hit == 0)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += game->camera.delta_dist_x;
			game->camera.mapx += game->camera.stepx;
			game->camera.side = 0;
		}
		else
		{
			side_dist[1] += game->camera.delta_dist_y;
			game->camera.mapy += game->camera.stepy;
			game->camera.side = 1;
		}
		check_hit(game);
	}
}

void	calc_step_and_dda(t_game *game, double *pos, double *side_dist)
{
	calc_step_dist(game, pos, side_dist);
	perform_dda(game, side_dist);
}
