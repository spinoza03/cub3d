/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:09:57 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/14 14:52:23 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	init_data(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img.img_ptr = NULL;
	game->north_texture = NULL;
	game->west_texture = NULL;
	game->south_texture = NULL;
	game->east_texture = NULL;
	game->width = WIN_WIDTH;
	game->height = WIN_HEIGHT;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->map = NULL;
	game->flags.no = 0;
	game->flags.so = 0;
	game->flags.we = 0;
	game->flags.east = 0;
	game->flags.floor = 0;
	game->flags.cealing = 0;
}

static void	free_parsing_data(t_game *game)
{
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->map)
		ft_free_split(game->map);
}

static void	free_mlx_images(t_game *game)
{
	if (game->img.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	if (game->tex_north.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_north.img_ptr);
	if (game->tex_south.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_south.img_ptr);
	if (game->tex_east.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_east.img_ptr);
	if (game->tex_west.img_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->tex_west.img_ptr);
}

static void	free_mlx_core(t_game *game)
{
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	free_all_data(t_game *game)
{
	free_parsing_data(game);
	free_mlx_images(game);
	free_mlx_core(game);
}
