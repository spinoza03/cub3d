/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:46:45 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/12 21:13:52 by bael-bad         ###   ########.fr       */
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
}

void	calc_step_and_dda(t_game *game, double *pos, double *side_dist)
{
	calc_step_dist(game, pos, side_dist);
	perform_dda(game, side_dist);
}

void	calc_wall_params(t_game *game, double *side_dist, int *draw)
{
	double	perp_wall_dist;
	int		line_height;

	if (game->camera.side == 0)
		perp_wall_dist = (side_dist[0] - game->camera.delta_dist_x);
	else
		perp_wall_dist = (side_dist[1] - game->camera.delta_dist_y);
	if (perp_wall_dist < 0.0001)
		perp_wall_dist = 0.0001;
	line_height = (int)(game->height / perp_wall_dist);
	draw[0] = -line_height / 2 + game->height / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_height / 2 + game->height / 2;
	if (draw[1] >= game->height)
		draw[1] = game->height - 1;
	draw[2] = line_height;
	draw[3] = (int)(perp_wall_dist * 1000);
}
