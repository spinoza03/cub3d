/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:46:19 by bael-bad          #+#    #+#             */
/*   Updated: 2025/12/07 16:46:22 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	free_all_data(t_game *game)
{
	free_parsing_data(game);
	free_mlx_images(game);
	free_mlx_core(game);
}
