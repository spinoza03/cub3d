/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:45:54 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/12 21:13:56 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

static void	init_ray_vars(t_game *game, double *pos, int x)
{
	game->camera.camerax = 2 * x / (double)game->width - 1;
	game->camera.raydirx = game->player.player_dir_x + \
		game->player.plane_x * game->camera.camerax;
	game->camera.raydiry = game->player.player_dir_y + \
		game->player.plane_y * game->camera.camerax;
	game->camera.mapx = (int)pos[0];
	game->camera.mapy = (int)pos[1];
	if (game->camera.raydirx == 0)
		game->camera.delta_dist_x = 1e30;
	else
		game->camera.delta_dist_x = fabs(1 / game->camera.raydirx);
	if (game->camera.raydiry == 0)
		game->camera.delta_dist_y = 1e30;
	else
		game->camera.delta_dist_y = fabs(1 / game->camera.raydiry);
}

static void	cast_ray(t_game *game, int x, double *pos)
{
	double	side_dist[2];
	int		draw[4];

	init_ray_vars(game, pos, x);
	calc_step_and_dda(game, pos, side_dist);
	calc_wall_params(game, side_dist, draw);
	render_column(game, x, pos, draw);
}

int	render_3d(t_game *game)
{
	int		x;
	double	pos[2];

	pos[0] = game->player.ply_x / game->img.cell_size;
	pos[1] = game->player.ply_y / game->img.cell_size;
	x = 0;
	while (x < game->width)
	{
		cast_ray(game, x, pos);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
		game->img.img_ptr, 0, 0);
	return (0);
}
