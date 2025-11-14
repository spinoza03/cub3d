/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:58:27 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/14 14:52:05 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

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
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}
