
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

int check_ext(char *str)
{
	char	*dot;

	dot = ft_strrchr(str, '.');
	if (dot == NULL || (ft_strcmp(dot, ".cub") != 0|| *(dot - 1) == '.'))
		return (0);
	else
		return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	init_data(&game);
	if (ac != 2)
	{
		ft_pustr_fd("invalid args\n", 2);
		exit (0);
	}
	else if (!check_ext(av[1]))
		ft_pustr_fd("Invalid file extension. Use .cub\n", 2);
	else if (!start_parsing(&game, av[1]))
	{
		ft_pustr_fd("Error: Invalid file\n", 2);
		free_all_data(&game);
		exit(1);
	}
	else if (!pars_map_validation(&game))
	{
		ft_pustr_fd("Error: Invalid map please fix it\n", 2);
		free_all_data(&game);
		exit(1);
	}
	// --- PARSING SUCCESSFUL ---
	// Now we call your friend's code to start the game
	
	// 1. Initialize Player (using parsed data)
	init_player(&game);
	
	// 2. Initialize MLX Window
	if (!init_win(&game))
	{
		ft_pustr_fd("Error: MLX failed to initialize\n", 2);
		free_all_data(&game);
		exit(1);
	}

	if (!load_textures(&game))
	{
		ft_pustr_fd("Error: Failed to load textures\n", 2);
		free_all_data(&game);
		exit(1);
	}
	// 3. Set up hooks and run the game loop
	// render_3d is the main raycasting loop
	mlx_loop_hook(game.mlx_ptr, render_3d, &game);
	// handle_key manages W, A, S, D, arrows
	mlx_hook(game.win_ptr, 2, 1L << 0, handle_key, &game);
	
	mlx_loop(game.mlx_ptr);
	
	// This part is reached after the window is closed
	free_all_data(&game);
	return (0);
}
