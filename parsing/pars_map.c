/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:50:22 by allali            #+#    #+#             */
/*   Updated: 2025/09/12 17:17:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	pars_north(char *line, char **north)
{
	int		fd;
	char	*trimed;

	fd = 0;
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		ft_pustr_fd("error in north param\n", 2);
		free(trimed);
		return 0;
	}
	else
		*north = ft_strdup(trimed);
	close(fd);
	free(trimed);
	return (1);
}

int	pars_south(char *line, char **south)
{
	int		fd;
	char	*trimed;

	fd = 0;
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		ft_pustr_fd("error in south param\n", 2);
		free(trimed);
		return 0;
	}
	else
		*south = ft_strdup(trimed);
	close(fd);
	free(trimed);
	return (1);
}
int	pars_east(char *line, char **east)
{
	int		fd;
	char	*trimed;

	fd = 0;
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		ft_pustr_fd("error in east param\n", 2);
		free(trimed);
		return 0;
	}
	else
		*east = ft_strdup(trimed);
	close(fd);
	free(trimed);
	return (1);
}

int	pars_west(char *line, char **west)
{
	int		fd;
	char	*trimed;

	fd = 0;
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		ft_pustr_fd("error in west param\n", 2);
		free(trimed);
		return 0;
	}
	else
		*west = ft_strdup(trimed);
	close(fd);
	free(trimed);
	return (1);
}

int	pars_conf(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(pars_north(line + 3, &data->north_texture));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return(pars_south(line + 3, &data->south_texture));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return(pars_east(line + 3, &data->east_texture));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return(pars_west(line + 3, &data->west_texture));
	// else if (ft_strncmp(line, "F ", 2))
	// 	pars_floor(line + 2, &data->floor_color);
	// else if (ft_strncmp(line, "C ", 2))
	// 	pars_ceiling(line + 2, &data->ceiling_color);
	else
		return (1);
}

int read_file(t_game *game, char *file)
{
	char	*line;
	int		fd;
	char	*ptr;

	fd = open(file , O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		ptr = line;
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			continue;
		}
		if (!pars_conf(ptr, &game->data))
		{
    		free(line);
    		return (0);
		}
		free(line);
	}
	return (1);
}
int	pars_map(t_game *game, char *file)
{
	if (!read_file(game, file))
		return (0);
	else
		return 1;
}
