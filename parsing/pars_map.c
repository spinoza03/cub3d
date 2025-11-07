/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:50:23 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/07 16:51:53 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	pars_map(char *line, t_list **head)
{
	char	*duped;
	t_list	*new_node;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	duped = ft_strdup(line);
	if (!duped)
		return (0);
	new_node = ft_lstnew(duped);
	if (!new_node)
	{
		free(duped);
		return (0);
	}
	ft_lstadd_back(head, new_node);
	return (1);
}
int	pars_texture(char *line, char **texture_ptr, int *flag)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if (*flag == 1)
		return (0);
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		free(trimed);
		return (0);
	}
	else
		*texture_ptr = ft_strdup(trimed);
	*flag = 1;
	close(fd);
	free(trimed);
	return (1);
}

int	pars_color(char *line, int *color_ptr, int *flag)
{
	char	**splited;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (0);
		i++;
	}
	splited = ft_split(line, ',');
	if (*flag == 1 || !check_count(splited, color_ptr))
	{
		ft_free_split(splited);
		return (0);
	}
	ft_free_split(splited);
	*flag = 1;
	return (1);
}
int	pars_conf(char *line, t_game *game, t_list **head)
{
	char	*trimed;
	int		ret_val;

	ret_val = 1;
	trimed = ft_strtrim(line, " \t");
	if (ft_strncmp(trimed, "NO ", 3) == 0)
		ret_val = pars_texture(trimed + 3, &game->north_texture, &game->flags.no);
	else if (ft_strncmp(trimed, "SO ", 3) == 0)
		ret_val = pars_texture(trimed + 3, &game->south_texture, &game->flags.so);
	else if (ft_strncmp(trimed, "EA ", 3) == 0)
		ret_val = pars_texture(trimed + 3, &game->east_texture, &game->flags.east);
	else if (ft_strncmp(trimed, "WE ", 3) == 0)
		ret_val = pars_texture(trimed + 3, &game->west_texture, &game->flags.we);
	else if (ft_strncmp(trimed, "F ", 2) == 0)
		ret_val = pars_color(trimed + 2, &game->floor_color, &game->flags.floor);
	else if (ft_strncmp(trimed, "C ", 2) == 0)
		ret_val = pars_color(trimed + 2, &game->ceiling_color, &game->flags.cealing);
	else if (ft_strchr1(line, '0') || ft_strchr1(line, '1'))
		ret_val = pars_map(line, head);
	else if (trimed[0] == '\n')
		ret_val = 1;
	else
		ret_val = 0;
	free(trimed);
	return (ret_val);
}
