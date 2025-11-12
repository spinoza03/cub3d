/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:00:11 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/12 20:59:33 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * \
		(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	init_win(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_WIDTH, \
		WIN_HEIGHT, "cub3d");
	if (!game->win_ptr)
		return (0);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, \
		WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, \
		&game->img.bits_per_pixel, &game->img.line_length, \
		&game->img.endian);
	return (1);
}
