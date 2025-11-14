/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:50:22 by allali            #+#    #+#             */
/*   Updated: 2025/11/14 15:26:06 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	is_line_whitespace(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	process_line(char *line, t_game *game, t_list **head)
{
	if (is_line_whitespace(line))
	{
		if (*head != NULL)
		{
			ft_pustr_fd("Error: Empty line within map definition.\n", 2);
			return (0);
		}
		return (2);
	}
	if (!pars_conf(line, game, head))
		return (0);
	return (1);
}

static int	read_all_lines(int fd, t_game *game, t_list **head)
{
	char	*line;
	int		status;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		status = process_line(line, game, head);
		if (status == 0)
		{
			free(line);
			return (0);
		}
		if (status == 2)
		{
			free(line);
			continue ;
		}
		free(line);
	}
	return (1);
}

int	read_file(t_game *game, char *file, t_list **head)
{
	int		fd;
	int		read_success;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_pustr_fd("Error: Cannot open file.\n", 2);
		return (0);
	}
	read_success = read_all_lines(fd, game, head);
	close(fd);
	return (read_success);
}

int	start_parsing(t_game *game, char *file)
{
	t_list				*head;

	head = NULL;
	if (!read_file(game, file, &head))
		return (0);
	if (!check_sum(game, &head))
		return (0);
	populate_arr(head, game);
	ft_lstclear(&head, free);
	return (1);
}
