/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:10:36 by allali            #+#    #+#             */
/*   Updated: 2025/11/14 15:25:56 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	check_ext(char *str)
{
	char	*dot;

	dot = ft_strrchr(str, '.');
	if (dot == NULL || (ft_strcmp(dot, ".cub") != 0 || *(dot - 1) == '.'))
		return (0);
	else
		return (1);
}

static int	parsing_checks(t_game *game, int ac, char **av)
{
	if (ac != 2)
	{
		ft_pustr_fd("invalid args\n", 2);
		return (0);
	}
	if (!check_ext(av[1]))
	{
		ft_pustr_fd("Invalid file extension. Use .cub\n", 2);
		return (0);
	}
	if (!start_parsing(game, av[1]))
	{
		ft_pustr_fd("Error: Invalid file\n", 2);
		return (0);
	}
	if (!pars_map_validation(game))
	{
		ft_pustr_fd("Error: Invalid map please fix it\n", 2);
		return (0);
	}
	return (1);
}

static int	initialize_and_run(t_game *game)
{
	init_player(game);
	if (!init_win(game))
	{
		ft_pustr_fd("Error: MLX failed to initialize\n", 2);
		return (0);
	}
	if (!load_textures(game))
	{
		ft_pustr_fd("Error: Failed to load textures\n", 2);
		return (0);
	}
	mlx_loop_hook(game->mlx_ptr, render_3d, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_key, game);
	mlx_loop(game->mlx_ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	init_data(&game);
	if (!parsing_checks(&game, ac, av))
	{
		free_all_data(&game);
		exit(1);
	}
	if (!initialize_and_run(&game))
	{
		free_all_data(&game);
		exit(1);
	}
	free_all_data(&game);
	return (0);
}
