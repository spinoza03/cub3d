
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

#include "../include/cub.h"
#include <unistd.h>

int check_ext(char *str)
{
	char	*dot;

	dot = ft_strrchr(str, '.');
	if (dot == NULL || (ft_strcmp(dot - 1, ".cub") != 0 && *(dot - 1) == '.'))
		return (0);
	else
		return (1);
}

int main (int ac, char **av)
{
	t_game	*game;
	if (ac != 2)
		perror("invalid args");
	if (!check_ext(av[1]))
		perror("Invalid file extension. Use .cub");
	if (!pars_map(game, av[1]))
		perror("invalid map");
}