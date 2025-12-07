/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:53:17 by bael-bad          #+#    #+#             */
/*   Updated: 2025/12/07 16:53:27 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	calc_wall_distance(t_game *game, double *side_dist,
	double *distance, double *fix_fisheye)
{
	double	lenght_vec;

	if (game->camera.side == 0)
		*distance = (side_dist[0] - game->camera.delta_dist_x);
	else
		*distance = (side_dist[1] - game->camera.delta_dist_y);
	lenght_vec = sqrt(game->camera.raydirx * game->camera.raydirx + \
		game->camera.raydiry * game->camera.raydiry);
	*fix_fisheye = *distance / lenght_vec;
}

void	calc_wall_params(t_game *game, double *side_dist, int *draw)
{
	double	distance;
	double	fix_fisheye;
	int		line_height;

	calc_wall_distance(game, side_dist, &distance, &fix_fisheye);
	line_height = (int)(game->height / fix_fisheye);
	draw[0] = -line_height / 2 + game->height / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_height / 2 + game->height / 2;
	if (draw[1] >= game->height)
		draw[1] = game->height - 1;
	draw[2] = line_height;
	draw[3] = (int)(fix_fisheye * 1000);
}
