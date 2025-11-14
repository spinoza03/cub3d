/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:40:53 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/14 14:57:18 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	load_single_texture(t_game *game, char *path, t_img *tex_img)
{
	int	width;
	int	height;

	tex_img->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&width, &height);
	if (tex_img->img_ptr == NULL)
	{
		ft_pustr_fd("Error: Failed to load texture: ", 2);
		ft_pustr_fd(path, 2);
		ft_pustr_fd("\n", 2);
		return (0);
	}
	tex_img->addr = mlx_get_data_addr(tex_img->img_ptr,
			&tex_img->bits_per_pixel,
			&tex_img->line_length,
			&tex_img->endian);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_single_texture(game, game->north_texture, &game->tex_north))
		return (0);
	if (!load_single_texture(game, game->south_texture, &game->tex_south))
		return (0);
	if (!load_single_texture(game, game->east_texture, &game->tex_east))
		return (0);
	if (!load_single_texture(game, game->west_texture, &game->tex_west))
		return (0);
	return (1);
}
