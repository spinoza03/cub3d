/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:50:22 by allali            #+#    #+#             */
/*   Updated: 2025/09/15 18:35:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <stdio.h>

int	pars_north(char *line, char **north, t_data *data)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if(data->flags.no == 1)
		return (0);
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
	data->flags.no = 1;
	close(fd);
	free(trimed);
	return (1);
}

int	pars_south(char *line, char **south, t_data *data)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if(data->flags.so == 1)
		return (0);
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
	data->flags.so = 1;
	close(fd);
	free(trimed);
	return (1);
}
int	pars_east(char *line, char **east, t_data *data)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if(data->flags.east == 1)
		return (0);
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
	data->flags.east = 1;
	close(fd);
	free(trimed);
	return (1);
}

int	pars_west(char *line, char **west, t_data *data)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if(data->flags.we == 1)
		return (0);
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
	data->flags.we = 1;
	close(fd);
	free(trimed);
	return (1);
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
	while (colors[i])
	{
		if (!is_valid_integer(colors[i]))
			return (0);
		c[i] = ft_atoi(colors[i]);
		if(c[i] > 255 || c[i] < 0)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	*final_color = (c[0] << 16 | c[1] << 8 | c[2]);
	return (1);
}
int	pars_floor(char *line, int *f, t_data *data)
{
	char	**splited;

	splited = ft_split(line, ',');
	if(data->flags.floor == 1 || !check_count(splited, f))
		return 0;
	data->flags.floor = 1;
	return 1;
}

int	pars_ceiling(char *line, int *f, t_data *data)
{
	char	**splited;

	splited = ft_split(line, ',');
	if(data->flags.cealing == 1 || !check_count(splited, f))
		return 0;
	data->flags.cealing = 1;
	return 1;
}

int	pars_conf(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(pars_north(line + 3, &data->north_texture, data));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return(pars_south(line + 3, &data->south_texture, data));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return(pars_east(line + 3, &data->east_texture, data));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return(pars_west(line + 3, &data->west_texture, data));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (pars_floor(line + 2, &data->floor_color, data));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (pars_ceiling(line + 2, &data->ceiling_color, data));
	else
		return (1);
}

int read_file(t_game *game, char *file)
{
	char	*line;
	int		fd;
	char	*ptr;

	fd = open(file , O_RDONLY);
	while (1) //?
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
