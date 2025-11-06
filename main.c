
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

void	free_all_data(t_game *game)
{
	// 1. Free all the parsing data (paths and map)
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->map)
		ft_free_split(game->map); // Your function from pars_map.c

	// 2. Free the MLX image
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
	// 3. Free the MLX window
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);

	// 4. Free the MLX display pointer
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

int	is_valid_char(char *str)
{
	int		i;
	char	*valid_map_chars;

	valid_map_chars = "01NSEW ";
	i = 0;
	while (str[i])
	{
		if (!ft_strchr1(valid_map_chars, str[i]))
		{
			printf(", here the problem-->[%c]", str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	find_player(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr1("NSEW", game->map[y][x]))
			{
				player_count++;
				game->player_x = x;
				game->player_y = y;
				game->player_dir_char = game->map[y][x];
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

int	check_chars(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (!is_valid_char(game->map[i]))
			return (0);
		i++;
	}
	if (!find_player(game))
		return (0);
	return (1);
}
int	check_neighbors(t_game *game, int y, int x)
{
	if (y == 0)
		return (0);
	if (x >= (int)ft_strlen(game->map[y - 1]) || game->map[y - 1][x] == ' ')
		return (0);
	if (y == game->map_height - 1)
		return (0);
	if (x >= (int)ft_strlen(game->map[y + 1]) || game->map[y + 1][x] == ' ')
		return (0);
	if (x == 0 || game->map[y][x - 1] == ' ')
		return (0);
	if (x + 1 >= (int)ft_strlen(game->map[y]) || game->map[y][x + 1] == ' ')
		return (0);
	return (1);
}
int	pars_map_validation(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	if (!check_chars(game))
	{
		printf("DEBUG: The error is coming from check_chars()!\n");
		return (0);
	}
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr1("0NSEW", game->map[y][x]))
				if (!check_neighbors(game, y, x))
				{
					printf("DEBUG: The error from check_neighbors() at [%d][%d]!\n", y, x);
					return (0);
				}
			x++;
		}
		y++;
	}
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
