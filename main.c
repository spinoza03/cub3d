
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:10:36 by allali            #+#    #+#             */
/*   Updated: 2025/09/04 21:00:42 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"
#include <stdio.h>

int check_ext(char *str)
{
	char	*dot;

	dot = ft_strrchr(str, '.');
	if (dot == NULL || (ft_strcmp(dot, ".cub") != 0|| *(dot - 1) == '.'))
		return (0);
	else
		return (1);
}
void init_data(t_data *game)
{
	game->north_texture = NULL;
	game->west_texture = NULL;
	game->south_texture = NULL;
	game->east_texture = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->map = NULL;
}
int main (int ac, char **av)
{
	t_game	game;

	init_data(&game.data);
	if (ac != 2)
		ft_pustr_fd("invalid args\n", 2);
	else if (!check_ext(av[1]))
		ft_pustr_fd("Invalid file extension. Use .cub\n", 2);
	else if (!pars_map(&game, av[1]))
		perror("invalid map");
}