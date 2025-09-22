
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

void	free_data(t_data *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->west_texture)
		free(data->west_texture);
	// add free for map
}

int	is_valid_char(char *str)
{
	int		i;
	char	*valid_map_chars;

	valid_map_chars = "01NSEW ";
	i = 0;
	while (str[i])
	{
		if(!ft_strchr1(valid_map_chars, str[i]))
		{
			printf(", here the problem-->[%c]", str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	find_player(t_data *data)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if(ft_strchr1("NSEW", data->map[y][x]))
			{
				player_count++;
				data->player_x = x;
				data->player_y = y;
				data->player_dir = data->map[y][x];
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

int	check_chars(t_data *data)
{
	int i;

	i = 0;
	while(data->map[i])
	{
		if(!is_valid_char(data->map[i]))
			return (0);
		i++;
	}
	if(!find_player(data))
		return (0);
	return (1);
}
int	check_neighbors(t_data *data, int y, int x)
{
	if (y == 0)
		return (0);
	if (x >= (int)ft_strlen(data->map[y - 1]) || data->map[y - 1][x] == ' ')
		return (0);
	if (y == data->map_height - 1)
		return (0);
	if (x >= (int)ft_strlen(data->map[y + 1]) || data->map[y + 1][x] == ' ')
		return (0);
	if (x == 0 || data->map[y][x - 1] == ' ')
		return (0);
	if (x + 1 >= (int)ft_strlen(data->map[y]) || data->map[y][x + 1] == ' ')
		return (0);
	return (1);
}
int	pars_map_validation(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if(!check_chars(data))
	{
		printf("DEBUG: The error is coming from check_chars()!\n");
		return (0);
	}
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if(ft_strchr1("0NSEW", data->map[y][x]))
				if(!check_neighbors(data, y, x))
				{
					printf("DEBUG: The error is from check_neighbors() at [%d][%d]!\n", y, x);
					return (0);
				}
			x++;
		}
		y++;
	}
	return (1);
}
int main (int ac, char **av)
{
	t_game	game;

	init_data(&game.data);
	if (ac != 2)
		ft_pustr_fd("invalid args\n", 2);
	else if (!check_ext(av[1]))
		ft_pustr_fd("Invalid file extension. Use .cub\n", 2);
	else if (!start_parsing(&game, av[1]))
    {
		ft_pustr_fd("Invalid file\n", 2);
        exit(1);
    }
	else if (!pars_map_validation(&game.data))
    {
		ft_pustr_fd("Invalid map please fix it", 2);
        exit(1);
    }
	else if (!init_game(&game))
    {
        ft_pustr_fd("Erreur in init", 2);
        exit(1);
    }
    printf("dfghjj\n");

	mlx_loop_hook(game.mlx_ptr, render, &game);
	mlx_loop(game.mlx_ptr);

	// printf("color : %d\n", game.data.floor_color);
	// printf("color2 : %d\n", game.data.ceiling_color);
	free_data(&game.data);
	free_game_data(&game.data);
}
