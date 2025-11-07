/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:45:09 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/07 16:47:48 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_valid_integer(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
int	check_count(char **colors, int *final_color)
{
	int	i;
	int	c[3];

	i = 0;
	if (!colors[i] || colors[i][0] == '\0')
		return (0);
	while (colors[i])
	{
		if (!is_valid_integer(colors[i]))
			return (0);
		c[i] = ft_atoi(colors[i]);
		if (c[i] > 255 || c[i] < 0)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	*final_color = (c[0] << 16 | c[1] << 8 | c[2]);
	return (1);
}

int	check_sum(t_game *game, t_list **head)
{
	int	flag_sum;

	flag_sum = game->flags.no + game->flags.so +
				game->flags.we + game->flags.east +
				game->flags.floor + game->flags.cealing;
	if (flag_sum != 6)
	{
		ft_pustr_fd("Error: Missing one or more configurations.\n", 2);
		ft_lstclear(head, free);
		return (0);
	}
	return (1);
}