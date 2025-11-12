/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:48:59 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/12 21:01:13 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static t_img	*choose_texture(t_game *game)
{
	if (game->camera.side == 1)
	{
		if (game->camera.raydiry > 0)
			return (&game->tex_south);
		else
			return (&game->tex_north);
	}
	else
	{
		if (game->camera.raydirx > 0)
			return (&game->tex_east);
		else
			return (&game->tex_west);
	}
}

static int	calc_texture_x(t_game *game, double *pos, int draw_perp)
{
	double	wall_x;
	double	perp_wall_dist;
	int		tex_x;

	perp_wall_dist = draw_perp / 1000.0;
	if (game->camera.side == 0)
		wall_x = pos[1] + perp_wall_dist * game->camera.raydiry;
	else
		wall_x = pos[0] + perp_wall_dist * game->camera.raydirx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (game->camera.side == 0 && game->camera.raydirx > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (game->camera.side == 1 && game->camera.raydiry < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

static void	draw_walls(t_game *game, t_draw_data *data)
{
	int				y;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;

	step = 1.0 * TEX_HEIGHT / data->draw[2];
	tex_pos = (data->draw[0] - game->height / 2 + data->draw[2] / 2) * step;
	y = data->draw[0];
	while (y < data->draw[1])
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_pixel(data->texture, data->tex_x, tex_y);
		if (game->camera.side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->img, data->x, y, color);
		y++;
	}
}

void	render_column(t_game *game, int x, double *pos, int *draw)
{
	t_draw_data	data;
	int			y;

	data.x = x;
	data.draw = draw;
	data.texture = choose_texture(game);
	data.tex_x = calc_texture_x(game, pos, draw[3]);
	y = 0;
	while (y < draw[0])
	{
		my_mlx_pixel_put(&game->img, x, y, game->ceiling_color);
		y++;
	}
	draw_walls(game, &data);
	y = draw[1];
	while (y < game->height)
	{
		my_mlx_pixel_put(&game->img, x, y, game->floor_color);
		y++;
	}
}
